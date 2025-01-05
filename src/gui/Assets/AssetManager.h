#pragma once

#include "gui/Assets/Asset.h"
#include <filesystem>
#include <map>
#include <raylib.h>
#include <vector>

class AssetManager {

public:
    AssetManager(std::filesystem::path assetPath);
    ~AssetManager();
    static AssetManager& get() { return *m_instance; }

    void update();
    bool setActiveWindow(int windowId);

    Font getFont(std::filesystem::path filename, int size);
    Texture2D getSvg(std::filesystem::path filename, int width, int height);
    Texture2D getImage(std::filesystem::path filename);

private:
    void addWindowContainers();

private:
    static inline AssetManager* m_instance = nullptr;
    int m_currentWindowId = -1;
    std::map<int, std::vector<FontAsset>> m_fontMap;
    std::map<int, std::vector<SvgAsset>> m_svgMap;
    std::map<int, std::vector<ImageAsset>> m_imageMap;
    std::filesystem::path m_assetPath;
};