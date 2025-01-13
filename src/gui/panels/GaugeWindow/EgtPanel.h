#pragma once

#include "gui/components/SmallGauge.h"
#include "gui/panels/Panel.h"

class EgtPanel : public Panel {

public:
    EgtPanel();
    virtual ~EgtPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    int m_titleSize = 40;
};