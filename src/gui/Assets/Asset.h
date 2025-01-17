#pragma once

#include <filesystem>
#include <raylib.h>

struct FontAsset {
    Font font = {};
    std::filesystem::path filepath;
    int size;
    bool loaded = false;
};

struct SvgAsset {
    Texture2D texture = {};
    std::filesystem::path filepath;
    int width;
    int height;
    bool loaded = false;
};

struct ImageAsset {
    Texture2D texture = {};
    std::filesystem::path filepath;
    bool loaded = false;
};

struct CameraAsset {
    Texture2D texture = {};
    std::string name;
};