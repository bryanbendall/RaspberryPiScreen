#pragma once

#include "BrytecConfigEmbedded/Usb/UsbDefs.h"
#include <asio.hpp>
#include <deque>
#include <map>
#include <memory>
#include <mutex>

using asio::ip::tcp;

struct ci_less {
    // case-independent (ci) compare_less binary function
    struct nocase_compare {
        bool operator()(const unsigned char& c1, const unsigned char& c2) const
        {
            return tolower(c1) < tolower(c2);
        }
    };
    bool operator()(const std::string& s1, const std::string& s2) const
    {
        return std::lexicographical_compare(s1.begin(), s1.end(), // source range
            s2.begin(), s2.end(), // dest range
            nocase_compare()); // comparison
    }
};

class HttpConnectionHandler : public std::enable_shared_from_this<HttpConnectionHandler> {

public:
    HttpConnectionHandler(asio::io_context& io_context);
    static std::shared_ptr<HttpConnectionHandler> create(asio::io_context& io_context);
    tcp::socket& socket() { return m_socket; }
    void start();

private:
    void readFirstLine(const asio::error_code& err, size_t bytes_transferred);
    void readNextLine(const asio::error_code& err, size_t bytes_transferred);
    void decodeHeader(std::string line);
    int getContentLength();
    void handleAndRespond();
    void handleWrite(const asio::error_code& err, size_t bytes_transferred);
    void startRead();

private:
    tcp::socket m_socket;
    asio::streambuf m_readBuffer;
    std::string m_method;
    std::string m_url;
    std::string m_version;
    std::string m_content;
    std::map<std::string, std::string, ci_less> m_headers;
};