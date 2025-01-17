#include "AssetManager.h"

#include "gui/CameraController.h"
#include <raymath.h>

AssetManager::AssetManager(std::filesystem::path assetPath)
    : m_assetPath(assetPath)
{
    m_instance = this;
}

AssetManager::~AssetManager()
{
}

void AssetManager::update()
{
    for (auto& windowFonts : m_fontMap) {
        if (setActiveWindow(windowFonts.first)) {
            for (auto& fontAsset : windowFonts.second) {
                if (!fontAsset.loaded) {
                    std::filesystem::path path = m_assetPath / "fonts" / fontAsset.filepath;
                    fontAsset.font = LoadFontEx(path.string().c_str(), fontAsset.size, 0, 250);
                    fontAsset.loaded = true;
                }
            }
        }
    }

    for (auto& windowSvgs : m_svgMap) {
        if (setActiveWindow(windowSvgs.first)) {
            for (auto& svgAsset : windowSvgs.second) {
                if (!svgAsset.loaded) {
                    std::filesystem::path path = m_assetPath / "images" / svgAsset.filepath;
                    Image img = LoadImageSvg(path.string().c_str(), svgAsset.width, svgAsset.height);
                    svgAsset.texture = LoadTextureFromImage(img);
                    UnloadImage(img);
                    svgAsset.loaded = true;
                }
            }
        }
    }

    for (auto& windowImages : m_imageMap) {
        if (setActiveWindow(windowImages.first)) {
            for (auto& imageAsset : windowImages.second) {
                if (!imageAsset.loaded) {
                    std::filesystem::path path = m_assetPath / "images" / imageAsset.filepath;
                    Image img = LoadImage(path.string().c_str());
                    imageAsset.texture = LoadTextureFromImage(img);
                    UnloadImage(img);
                    imageAsset.loaded = true;
                }
            }
        }
    }
}

bool AssetManager::setActiveWindow(int windowId)
{
    if (SetActiveWindowContext(windowId) < 0)
        return false;

    m_currentWindowId = windowId;
    addWindowContainers();
    return true;
}

Font* AssetManager::getFont(std::filesystem::path filename, int size)
{
    if (m_currentWindowId < 0)
        return nullptr;

    for (auto& fontAsset : m_fontMap[m_currentWindowId]) {
        if (fontAsset.filepath == filename && fontAsset.size == size)
            return IsFontReady(fontAsset.font) ? &fontAsset.font : nullptr;
    }

    // We dont have this asset yet, create it
    FontAsset newFontAsset;
    newFontAsset.filepath = filename;
    newFontAsset.size = size;
    m_fontMap[m_currentWindowId].push_back(newFontAsset);
    return nullptr;
}

Texture2D* AssetManager::getSvg(std::filesystem::path filename, int width, int height)
{
    if (m_currentWindowId < 0)
        return nullptr;

    for (auto& svgAsset : m_svgMap[m_currentWindowId]) {
        if (svgAsset.filepath == filename && svgAsset.width == width && svgAsset.height == height)
            return IsTextureReady(svgAsset.texture) ? &svgAsset.texture : nullptr;
    }

    // We dont have this asset yet, create it
    SvgAsset newsvgAsset;
    newsvgAsset.filepath = filename;
    newsvgAsset.width = width;
    newsvgAsset.height = height;
    m_svgMap[m_currentWindowId].push_back(newsvgAsset);
    return nullptr;
}

Texture2D* AssetManager::getImage(std::filesystem::path filename)
{
    if (m_currentWindowId < 0)
        return nullptr;

    for (auto& imageAsset : m_imageMap[m_currentWindowId]) {
        if (imageAsset.filepath == filename)
            return IsTextureReady(imageAsset.texture) ? &imageAsset.texture : nullptr;
    }

    // We dont have this asset yet, create it
    ImageAsset newImageAsset;
    newImageAsset.filepath = filename;
    m_imageMap[m_currentWindowId].push_back(newImageAsset);
    return nullptr;
}

Texture2D* AssetManager::getCameraTexture(const std::string& name)
{
    RemoteCamera& camera = CameraController::get().getCamera(name);
    if (!camera.isOpen())
        return nullptr;

    Vector2 cameraSize = camera.getSize();
    if (Vector2Equals(cameraSize, Vector2Zero()))
        return nullptr;

    for (auto& cameraAsset : m_cameraMap[m_currentWindowId]) {
        if (cameraAsset.name == name) {
            // Update texture and return it
            Texture2D& texture = cameraAsset.texture;
            if (texture.width == cameraSize.x && texture.height == cameraSize.y) {
                // Our size matches so just update texture
                UpdateTexture(texture, camera.getData());
                return &texture;
            } else {
                // Size has changes so unload old and create new
                if (IsTextureReady(texture))
                    UnloadTexture(texture);

                Image img = GenImageColor(cameraSize.x, cameraSize.y, WHITE);
                ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
                texture = LoadTextureFromImage(img);
                UpdateTexture(texture, camera.getData());
                UnloadImage(img);
                return &texture;
            }
        }
    }

    // Create texture
    CameraAsset newCameraAsset;
    newCameraAsset.name = name;
    Image img = GenImageColor(cameraSize.x, cameraSize.y, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    newCameraAsset.texture = LoadTextureFromImage(img);
    UpdateTexture(newCameraAsset.texture, camera.getData());
    UnloadImage(img);
    m_cameraMap[m_currentWindowId].push_back(newCameraAsset);
    return &m_cameraMap[m_currentWindowId].back().texture;
}

void AssetManager::addWindowContainers()
{
    if (m_fontMap.find(m_currentWindowId) == m_fontMap.end())
        m_fontMap[m_currentWindowId];

    if (m_svgMap.find(m_currentWindowId) == m_svgMap.end())
        m_svgMap[m_currentWindowId];

    if (m_imageMap.find(m_currentWindowId) == m_imageMap.end())
        m_imageMap[m_currentWindowId];

    if (m_cameraMap.find(m_currentWindowId) == m_cameraMap.end())
        m_cameraMap[m_currentWindowId];
}