#pragma once

#include "gui/panels/Panel.h"

class RightMainPanel : public Panel {

public:
    RightMainPanel();
    virtual ~RightMainPanel();

    void draw(int width, int height) override;
};