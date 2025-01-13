#include "LabelButton.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/input/TouchInput.h"

LabelButton::LabelButton(std::string label, Rectangle rect, bool showOutline)
    : m_rect(rect)
    , m_label(label)
    , m_showOutline(showOutline)
{
    draw();
}

LabelButton::operator bool() const
{
    TouchInput* touch = TouchInput::get();
    if (!touch)
        return false;

    if (touch->isClicked(m_rect))
        return true;

    return false;
}

void LabelButton::draw()
{
    TouchInput* touch = TouchInput::get();
    if (touch) {
        if (touch->isDown(m_rect))
            DrawRectangleRec(m_rect, GetColor(GlobalOutputs::gray));
    }

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", m_labelSize);
    if (font) {
        Vector2 labelSize = MeasureTextEx(*font, m_label.c_str(), m_labelSize, 0);
        Vector2 labelPosition = { m_rect.x + (m_rect.width / 2.0f) - (labelSize.x / 2.0f), m_rect.y + (m_rect.height / 2.0f) - (m_labelSize / 2.0f) };
        DrawTextEx(*font, m_label.c_str(), labelPosition, m_labelSize, 0, GetColor(GlobalOutputs::white));
    }

    if (m_showOutline)
        DrawRectangleLinesEx(m_rect, 1.0f, GetColor(GlobalOutputs::gray));
}