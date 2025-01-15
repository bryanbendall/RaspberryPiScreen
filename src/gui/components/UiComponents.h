#pragma once

#include <filesystem>
#include <raylib.h>
#include <string>

namespace Ui {

void SmallGauge(Vector2 center, float size, std::string label, std::filesystem::path iconFilename, float value, float min = 0.0f, float max = 100.0f, int decimals = 0);
void Indicator(Vector2 position, int size, std::filesystem::path iconFilename, float value, Color activeColor);
void Tach(Vector2 center, float size, float value, float revLimit);
void BoostGauge(Vector2 position, float value);
void ClosedLoopGauge(Vector2 position, float value);
void Speedometer(Vector2 center, float value, bool kph = false);
void AfrGauge(Vector2 center, float afr1, float afr2, bool showSecond = true);
void GearIndicator(Vector2 position, int size, float value);
void BarGauge(Vector2 position, Vector2 size, float value, std::filesystem::path iconFilename = "", std::string label = "", float min = 0.0f, float max = 100.0f);
bool Button(std::string label, Rectangle rect, int labelSize, bool showOutline = false);
}