#pragma once

#include "gui/panels/Panel.h"

class RightMapPanel : public Panel {

public:
    RightMapPanel();
    virtual ~RightMapPanel();

    void draw(int width, int height) override;

private:
    void updateValues();
};