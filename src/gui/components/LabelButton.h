#pragma once

#include <raylib.h>
#include <string>

class LabelButton {

public:
    LabelButton(std::string label, Rectangle rect, bool showOutline = false);
    operator bool() const;

private:
    void draw();

private:
    Rectangle m_rect;
    std::string m_label;
    bool m_showOutline;
    int m_labelSize = 42;
};