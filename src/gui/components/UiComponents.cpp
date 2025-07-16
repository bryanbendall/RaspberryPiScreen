#include "UiComponents.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include "gui/input/TouchInput.h"
#include <fmt/format.h>
#include <raymath.h>
#include <rlgl.h>

namespace Ui {

void SmallGauge(const SmallGaugeSpec& spec)
{
    float innerCircleSize = spec.size * 0.8f;
    float centerLableSize = spec.size * 0.27f;
    float unitLableSize = spec.size * 0.16f;
    float minMaxLableSize = spec.size * 0.11f;
    float iconSize = spec.size * 0.2f;

    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", centerLableSize);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", unitLableSize);
    Font* minMaxFont = AssetManager::get().getFont("RussoOne-Regular.ttf", unitLableSize);

    if (!largeFont || !smallFont || !minMaxFont)
        return;

    Texture2D* outerCircleTexture = AssetManager::get().getSvg("outerCircle.svg", spec.size, spec.size);
    Texture2D* innerCircleTexture = AssetManager::get().getSvg("circle.svg", innerCircleSize, innerCircleSize);
    Texture2D* warningTexture = AssetManager::get().getSvg("radial gradient.svg", spec.size, spec.size);
    Texture2D* iconTexture = nullptr;
    if (!spec.iconFilename.string().empty())
        iconTexture = AssetManager::get().getSvg(spec.iconFilename, iconSize, iconSize);

    if (!outerCircleTexture || !innerCircleTexture || !warningTexture)
        return;

    // Ring
    {
        float angle = Utils::mapValue(spec.min, spec.max, 90.0f, 360.0f, spec.value);

        DrawCircleSector(spec.center, spec.size / 2.0f, 90.0f, 360.0f, 20, GetColor(GlobalOutputs::gray));
        DrawCircleSector(spec.center, spec.size / 2.0f, 90.0f, angle, 20, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));

        DrawTexture(*outerCircleTexture, spec.center.x - (spec.size / 2.0f), spec.center.y - (spec.size / 2.0f), GetColor(GlobalOutputs::black));
        DrawTexture(*innerCircleTexture, spec.center.x - (innerCircleSize / 2.0f), spec.center.y - (innerCircleSize / 2.0f), GetColor(GlobalOutputs::black));

        if (spec.value < spec.lowWarning || spec.value > spec.highWarning)
            DrawTexture(*warningTexture, spec.center.x - (spec.size / 2.0f), spec.center.y - (spec.size / 2.0f), GetColor(GlobalOutputs::red));
    }

    // Center value text
    {
        std::string lable = fmt::format("{:.{}f}", spec.value, spec.decimals);
        Vector2 textSize = MeasureTextEx(*largeFont, lable.c_str(), centerLableSize, 0);
        DrawTextEx(*largeFont, lable.c_str(), { spec.center.x - (textSize.x / 2.0f), spec.center.y - (centerLableSize / 2.0f) }, centerLableSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge min and max text
    {
        std::string lable = fmt::format("{:.0f}", spec.min);
        DrawTextEx(*minMaxFont, lable.c_str(), { spec.center.x + 8.0f, spec.center.y + (spec.size / 2.0f) - minMaxLableSize }, minMaxLableSize, 0, GetColor(GlobalOutputs::white));

        lable = fmt::format("{:.0f}", spec.max);
        DrawTextEx(*minMaxFont, lable.c_str(), { spec.center.x + (innerCircleSize / 2.0f), spec.center.y + (minMaxLableSize / 4.0f) }, minMaxLableSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge label
    {
        Vector2 textSize = MeasureTextEx(*smallFont, spec.label.c_str(), unitLableSize, 0);
        DrawTextEx(*smallFont, spec.label.c_str(), { spec.center.x - (textSize.x / 2.0f), spec.center.y - (spec.size * 0.3f) }, unitLableSize, 0, GetColor(GlobalOutputs::gray));
    }

    // Icon
    {
        if (iconTexture)
            DrawTexture(*iconTexture, spec.center.x - (iconSize / 2.0f), spec.center.y + (spec.size * 0.14f), GetColor(GlobalOutputs::gray));
    }
}

void Indicator(Vector2 position, int size, std::filesystem::path iconFilename, float value, Color activeColor)
{
    Texture2D* icon = AssetManager::get().getSvg(iconFilename, size, size);

    if (!icon)
        return;

    if (value > 0.0001f)
        DrawTexture(*icon, position.x, position.y, activeColor);
}

void Tach(Vector2 center, float size, float value, float revLimit)
{
    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", 40);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", 16);

    if (!largeFont || !smallFont)
        return;

    Texture2D* colorTicks = AssetManager::get().getSvg("tach/ColorTicks.svg", 458, 426);
    Texture2D* bottomPanel = AssetManager::get().getSvg("tach/BottomPanel.svg", 244, 122);
    Texture2D* gaugeTexture = AssetManager::get().getSvg("tach/Gauge.svg", 476, 457);
    Texture2D* smallTicksTexture = AssetManager::get().getSvg("tach/SmallTicks.svg", 453, 422);

    Texture2D* needleTexture = AssetManager::get().getImage("tach/Needle.png");

    if (!colorTicks || !bottomPanel || !gaugeTexture || !smallTicksTexture || !needleTexture)
        return;

    // Background small ticks
    DrawTextureV(*smallTicksTexture, { center.x - (453.0f / 2.0f), 13.663f }, GetColor(GlobalOutputs::white));

    // Colored gauge amount
    float valueAngle = Utils::mapValue(0.0f, 10000.0f, 120.0f, 360.0f, value);
    Color gaugeColor = value > revLimit ? GetColor(GlobalOutputs::red) : Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    DrawCircleSector(center, size / 2.0f + 3.0f, 120.0f, valueAngle, 20, gaugeColor);

    // Rest of the gauge
    DrawTexture(*colorTicks, center.x - (458.0f / 2.0f), center.y - (426.0f / 2.0f) - 15.0f, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));
    DrawTextureV(*gaugeTexture, { center.x - (476.0f / 2.0f), 2.964f }, GetColor(GlobalOutputs::white));

    // Numbers
    int lableNumber = 10;
    for (int i = 90; i < 330; i += 24) {
        float angle = (float)i * DEG2RAD;
        float r = size / 2.0f - 60.0f;
        float x = r * std::sin(angle);
        float y = r * std::cos(angle);

        Color numberColor = lableNumber * 1000 + 1 > revLimit ? GetColor(GlobalOutputs::red) : GetColor(GlobalOutputs::white);

        std::string lable = fmt::format("{:d}", lableNumber);
        Vector2 fontSize = MeasureTextEx(*largeFont, lable.c_str(), 40, 0);
        DrawTextEx(*largeFont, lable.c_str(), { center.x + x - (fontSize.x / 2.0f), center.y + y - (fontSize.y / 2.0f) }, 40, 0, numberColor);
        lableNumber--;
    }

    // Needle
    {
        float mappedAngle = Utils::mapValue(0.0f, 10000.0f, 330.0f, 90.0f, value, false);
        float angle = mappedAngle * DEG2RAD;
        float r = size / 2.0f - 30.0f;
        float x = r * std::sin(angle);
        float y = r * std::cos(angle);

        rlPushMatrix();

        rlTranslatef(center.x, center.y, 0.0f);
        rlTranslatef(x, y, 0.0f);
        rlRotatef(-(angle * RAD2DEG) - 180.0f, 0.0f, 0.0f, 1.0f);

        DrawTexture(*needleTexture, -10, -60, WHITE);

        rlPopMatrix();
    }

    // Bottom panel
    DrawTexture(*bottomPanel, center.x - (244.0f / 2.0f), 350.0f, GetColor(GlobalOutputs::white));

    // Label
    std::string rpmLable = fmt::format("{:.0f}", value);
    DrawTextEx(*smallFont, rpmLable.c_str(), Vector2Add(center, { size / 2.0f - 20.0f, 20.0f }), 16.0f, 0.0f, GetColor(GlobalOutputs::white));
    DrawTextEx(*smallFont, "RPM", Vector2Add(center, { size / 2.0f - 20.0f, 36.0f }), 16.0f, 0.0f, GetColor(GlobalOutputs::gray));
}

void BoostGauge(Vector2 position, float value)
{
    int sectors = 3;
    int boarders = 60;
    int width = 150;

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", 24);
    Texture2D* maskTexture = AssetManager::get().getSvg("side gauge mask.svg", 150, 480);

    if (!font || !maskTexture)
        return;

    // Value bar
    float barTopY = Utils::mapValue(0.0f, (float)sectors * 10.0f, 480 - boarders, boarders, value);
    DrawRectangle(position.x, barTopY, width, 480 - boarders - barTopY, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));

    // White curved line
    DrawTextureV(*maskTexture, { position.x + 3.0f, position.y }, GetColor(GlobalOutputs::white));

    // Sector lines
    int tickHeight = (480 - (boarders * 2)) / sectors;
    for (int i = 0; i <= sectors; i++)
        DrawRectangle(position.x, tickHeight * i + boarders - 1, width, 2, GetColor(GlobalOutputs::white));

    // Mask
    DrawTextureV(*maskTexture, position, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x, 0, width, boarders - 1, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x, 480 - boarders + 1, width, boarders, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x + width, 0, 10, 480, GetColor(GlobalOutputs::black));

    // Scale numbers
    for (int i = 0; i <= sectors; i++) {

        float r = 60.0f;
        float y = (tickHeight * i + boarders);
        float circleY = y - 240.0f;
        float angle = (std::cos(-1.0f) * circleY) / r;
        float x = r * std::sin(angle + PI / 2.0f);

        std::string lable = fmt::format("{:d}", (sectors - i) * 10);
        Vector2 textSize = MeasureTextEx(*font, lable.c_str(), 24.0f, 0.0f);
        DrawTextEx(*font, lable.c_str(), { 640 - x - 240 - (textSize.x / 2.0f), y - (textSize.y / 2.0f) }, 24.0f, 0.0f, GetColor(GlobalOutputs::white));
    }

    // Label
    Vector2 textSize = MeasureTextEx(*font, "Boost", 24.0f, 0.0f);
    DrawTextEx(*font, "Boost", { position.x + 90.0f, 480.0f - boarders + 15.0f }, 24.0f, 0.0f, GetColor(GlobalOutputs::gray));
}

void ClosedLoopGauge(Vector2 position, float value)
{
    int boarders = 60;
    int width = 150;
    int sectors = 4;

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", 24);
    Texture2D* maskTexture = AssetManager::get().getSvg("side gauge mask.svg", 150, 480);

    if (!font || !maskTexture)
        return;

    // Value bar
    Color gaugeColor = value > 25.0f || value < -25.0f ? GetColor(GlobalOutputs::red) : Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    if (value > 0.0f) {
        float barTopY = Utils::mapValue(0.0f, 50.0f, 240, boarders, value);
        DrawRectangle(position.x, barTopY, width, 240 - barTopY, gaugeColor);
    } else {
        float barHeight = Utils::mapValue(0.0f, -50.0f, 240, 480 - boarders, value);
        DrawRectangle(position.x, 240, width, barHeight - 240, gaugeColor);
    }

    // White curved line
    Rectangle srcRect { 0, 0, -150, 480 };
    DrawTextureRec(*maskTexture, srcRect, { position.x - 3.0f, position.y }, GetColor(GlobalOutputs::white));

    // Sector lines
    int tickHeight = (480 - (boarders * 2)) / sectors;
    for (int i = 0; i <= sectors; i++)
        DrawRectangle(position.x, tickHeight * i + boarders - 1, width, 2, GetColor(GlobalOutputs::white));

    // Mask
    DrawTextureRec(*maskTexture, srcRect, position, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x, 0, width, boarders - 1, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x, 480 - boarders + 1, width, boarders, GetColor(GlobalOutputs::black));
    DrawRectangle(position.x - 10, 0, 10, 480, GetColor(GlobalOutputs::black));

    // Scale numbers
    for (int i = 0; i <= sectors; i++) {

        float r = 60.0f;
        float y = (tickHeight * i + boarders);
        float circleY = y - 240.0f;
        float angle = (std::cos(-1.0f) * circleY) / r;
        float x = r * std::sin(angle + PI / 2.0f);

        std::string lable = fmt::format("{:d}", (2 - i) * 25);
        Vector2 textSize = MeasureTextEx(*font, lable.c_str(), 24.0f, 0.0f);
        DrawTextEx(*font, lable.c_str(), { 640 + x + 215 + (textSize.x / 2.0f), y - (textSize.y / 2.0f) }, 24.0f, 0.0f, GetColor(GlobalOutputs::white));
    }

    // Label
    Vector2 textSize = MeasureTextEx(*font, "CL%", 24.0f, 0.0f);
    DrawTextEx(*font, "CL%", { position.x, 480.0f - boarders + 15.0f }, 24.0f, 0.0f, GetColor(GlobalOutputs::gray));
}

void Speedometer(Vector2 center, float value, bool kph)
{
    int largeFontSize = 100;
    int smallFontSize = 26;

    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", largeFontSize);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", smallFontSize);

    if (!largeFont || !smallFont)
        return;

    // Value
    if (kph)
        value = value * 1.609344f;
    std::string lable = fmt::format("{:.0f}", value);
    Vector2 valueMeasure = MeasureTextEx(*largeFont, lable.c_str(), largeFontSize, 0);
    DrawTextEx(*largeFont, lable.c_str(), { center.x - (valueMeasure.x / 2.0f), center.y - (valueMeasure.y / 2.0f) }, largeFontSize, 0, GetColor(GlobalOutputs::white));

    // Unit
    std::string unit = kph ? "KPH" : "MPH";
    Vector2 unitMeasure = MeasureTextEx(*smallFont, unit.c_str(), smallFontSize, 0);
    DrawTextEx(*smallFont, unit.c_str(), { center.x - (unitMeasure.x / 2.0f), center.y + (valueMeasure.y / 2.0f) - 10.0f }, smallFontSize, 0, GetColor(GlobalOutputs::gray));
}

void AfrGauge(Vector2 center, float afr1, float afr2, bool showSecond)
{
    int smallFontSize = 26;
    int largeFontSize = 40;

    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", largeFontSize);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", smallFontSize);

    if (!largeFont || !smallFont)
        return;

    std::string lable = "AFR";
    Vector2 afrSize = MeasureTextEx(*smallFont, lable.c_str(), smallFontSize, 0.0f);
    DrawTextEx(*smallFont, lable.c_str(), { center.x - (afrSize.x / 2.0f), center.y }, smallFontSize, 0, GetColor(GlobalOutputs::gray));

    if (!showSecond) {
        std::string lable = fmt::format("{:.1f}", afr1);
        Vector2 textSize = MeasureTextEx(*largeFont, lable.c_str(), largeFontSize, 0.0f);
        DrawTextEx(*largeFont, lable.c_str(), { center.x - (textSize.x / 2.0f), center.y + smallFontSize }, largeFontSize, 0, GetColor(GlobalOutputs::white));
    } else {
        std::string leftLable = fmt::format("{:.1f}", afr1);
        Vector2 leftSize = MeasureTextEx(*largeFont, leftLable.c_str(), largeFontSize, 0.0f);
        DrawTextEx(*largeFont, leftLable.c_str(), { center.x - leftSize.x - 10.0f, center.y + smallFontSize }, largeFontSize, 0, GetColor(GlobalOutputs::white));

        std::string rightLable = fmt::format("{:.1f}", afr2);
        DrawTextEx(*largeFont, rightLable.c_str(), { center.x + 10.0f, center.y + smallFontSize }, largeFontSize, 0, GetColor(GlobalOutputs::white));
    }
}

void GearIndicator(Vector2 position, int size, float value)
{
    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", size);

    if (!font)
        return;

    std::string lable = "E";
    int intVal = value;

    if (intVal == -2)
        lable = "P";

    if (intVal == -1)
        lable = "R";

    if (intVal == 0)
        lable = "N";

    if (intVal > 0)
        lable = fmt::format("{:d}", intVal);

    DrawTextEx(*font, lable.c_str(), position, size, 0, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));
}

void BarGauge(Vector2 position, Vector2 size, float value, std::filesystem::path iconFilename, std::string label, float min, float max)
{
    int iconSize = 30;
    int textSize = 20;

    DrawRectangleV(position, size, GetColor(GlobalOutputs::gray));
    float barX = Utils::mapValue(min, max, 0.0f, size.x, value);
    DrawRectangleV(position, { barX, size.y }, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));

    if (!iconFilename.empty()) {
        Texture2D* fuelIcon = AssetManager::get().getSvg(iconFilename, iconSize, iconSize);
        if (fuelIcon)
            DrawTexture(*fuelIcon, position.x - 40.0f, position.y - 10.0f, GetColor(GlobalOutputs::white));
    }

    if (!label.empty()) {
        Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", textSize);
        if (font) {
            Vector2 textMeasure = MeasureTextEx(*font, label.c_str(), textSize, 0);
            Vector2 labelPos = Vector2Subtract(position, { textMeasure.x + 10.0f, (textSize - size.y) / 2.0f });
            DrawTextEx(*font, label.c_str(), labelPos, textSize, 0.0f, GetColor(GlobalOutputs::white));
        }
    }
}

bool ButtonClick(Rectangle rect)
{
    TouchInput* touch = TouchInput::get();
    if (!touch)
        return false;

    if (touch->isClicked(rect))
        return true;

    return false;
}

bool Button(std::string label, Rectangle rect, int labelSize, bool showOutline, bool highlightBackground)
{
    if (highlightBackground)
        DrawRectangleRec(rect, Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]));

    TouchInput* touch = TouchInput::get();
    if (touch) {
        if (touch->isDown(rect))
            DrawRectangleRec(rect, GetColor(GlobalOutputs::gray));
    }

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", labelSize);
    if (font) {
        Vector2 labelMeasure = MeasureTextEx(*font, label.c_str(), labelSize, 0);
        Vector2 labelPosition = { rect.x + (rect.width / 2.0f) - (labelMeasure.x / 2.0f), rect.y + (rect.height / 2.0f) - (labelSize / 2.0f) };
        DrawTextEx(*font, label.c_str(), labelPosition, labelSize, 0, GetColor(GlobalOutputs::white));
    }

    if (showOutline)
        DrawRectangleLinesEx(rect, 1.0f, GetColor(GlobalOutputs::gray));

    return ButtonClick(rect);
}

void Text(Vector2 center, std::string label, int labelSize, Color tint)
{
    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", labelSize);

    if (!largeFont)
        return;

    Vector2 textSize = MeasureTextEx(*largeFont, label.c_str(), labelSize, 0);
    DrawTextEx(*largeFont, label.c_str(), { center.x - (textSize.x / 2.0f), center.y - (labelSize / 2.0f) }, labelSize, 0, tint);
}
}