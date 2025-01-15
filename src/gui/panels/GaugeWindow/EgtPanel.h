#pragma once

#include "gui/panels/Panel.h"

class EgtPanel : public Panel {

public:
    EgtPanel();
    virtual ~EgtPanel();

    void draw(int width, int height) override;
};