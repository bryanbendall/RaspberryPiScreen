#include "HttpConnectionHandler.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/CameraController.h"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

HttpConnectionHandler::HttpConnectionHandler(asio::io_context& io_context)
    : m_socket(io_context)
{
}

std::shared_ptr<HttpConnectionHandler> HttpConnectionHandler::create(asio::io_service& io_context)
{
    return std::shared_ptr<HttpConnectionHandler>(new HttpConnectionHandler(io_context));
}

void HttpConnectionHandler::start()
{
    startRead();
}

void HttpConnectionHandler::readFirstLine(const asio::error_code& err, size_t bytes_transferred)
{
    if (err) {
        std::cerr << "Error - HttpConnectionHandler::readFirstLine: " << err.message() << std::endl;
        m_socket.close();
        return;
    }

    if (bytes_transferred > 0) {

        std::string line, ignore;
        std::istream stream { &m_readBuffer };
        std::getline(stream, line, '\r');
        std::getline(stream, ignore, '\n');

        std::stringstream ssRequestLine(line);
        ssRequestLine >> m_method;
        ssRequestLine >> m_url;
        ssRequestLine >> m_version;

        asio::async_read_until(m_socket, m_readBuffer, '\r',
            std::bind(&HttpConnectionHandler::readNextLine,
                shared_from_this(),
                asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
}

void HttpConnectionHandler::readNextLine(const asio::error_code& err, size_t bytes_transferred)
{
    if (err) {
        std::cerr << "Error - HttpConnectionHandler::readNextLine: " << err.message() << std::endl;
        m_socket.close();
        return;
    }

    std::string line, ignore;
    std::istream stream { &m_readBuffer };
    std::getline(stream, line, '\r');
    std::getline(stream, ignore, '\n');
    decodeHeader(line);

    if (line.length() == 0) {

        if (getContentLength() > 0)
            std::getline(stream, m_content);

        handleAndRespond();

    } else {
        asio::async_read_until(m_socket, m_readBuffer, '\r',
            std::bind(&HttpConnectionHandler::readNextLine,
                shared_from_this(),
                asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
}

void HttpConnectionHandler::decodeHeader(std::string line)
{
    std::stringstream ssHeader(line);
    std::string headerName;
    std::getline(ssHeader, headerName, ':');

    std::string value;
    std::getline(ssHeader, value);
    m_headers[headerName] = value;
}

int HttpConnectionHandler::getContentLength()
{
    auto request = m_headers.find("content-length");
    if (request != m_headers.end()) {
        std::stringstream ssLength(request->second);
        int content_length;
        ssLength >> content_length;
        return content_length;
    }

    return 0;
}

void HttpConnectionHandler::handleAndRespond()
{
    std::stringstream ssOut;

    std::cout << "Response for: " << m_url << " " << m_method << std::endl;

    if (m_method == "POST") {
        if (m_url == "/left") {
            GlobalOutputs::engineLight = GlobalOutputs::engineLight ? 0.0f : 1.0f;
        } else if (m_url == "/right") {
            GlobalOutputs::engineLight = GlobalOutputs::engineLight ? 0.0f : 1.0f;
        } else if (m_url == "/camera") {
            RemoteCamera& screenCaptureCamera = CameraController::get().getCamera("ScreenCapture");
            screenCaptureCamera.open(m_content);
        } else if (m_url == "/stopcamera") {
            RemoteCamera& screenCaptureCamera = CameraController::get().getCamera("ScreenCapture");
            screenCaptureCamera.close();
        }

        ssOut << "HTTP/1.1 200 OK" << std::endl;
        ssOut << "content-type: text/html" << std::endl;
        ssOut << std::endl;
    }

    if (m_method == "GET") {
        if (m_url == "/") {

            std::ifstream t("../src/data/communication/http/index.html");
            std::string sHTML((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

            ssOut << "HTTP/1.1 200 OK" << std::endl;
            ssOut << "content-type: text/html" << std::endl;
            ssOut << "content-length: " << sHTML.length() << std::endl;
            ssOut << std::endl;
            ssOut << sHTML;
        } else {
            std::cout << "Cannot find response!" << std::endl;

            std::string sHTML = "<html><body><h1>404 Not Found</h1><p>There's nothing here. asdhfjshfkjdshfs</p></body></html>";
            ssOut << "HTTP/1.1 404 Not Found" << std::endl;
            ssOut << "content-type: text/html" << std::endl;
            ssOut << "content-length: " << sHTML.length() << std::endl;
            ssOut << std::endl;
            ssOut << sHTML;
        }
    }

    asio::async_write(
        m_socket,
        asio::buffer(ssOut.str().c_str(), ssOut.str().length()),
        std::bind(&HttpConnectionHandler::handleWrite,
            shared_from_this(),
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
}

void HttpConnectionHandler::handleWrite(const asio::error_code& err, size_t bytes_transferred)
{
    if (err) {
        std::cerr << "Error - HttpConnectionHandler::handleWrite : " << err.message() << std::endl;
        m_socket.close();
        return;
    }
}

void HttpConnectionHandler::startRead()
{
    asio::async_read_until(m_socket, m_readBuffer, '\r',
        std::bind(&HttpConnectionHandler::readFirstLine,
            shared_from_this(),
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
}
