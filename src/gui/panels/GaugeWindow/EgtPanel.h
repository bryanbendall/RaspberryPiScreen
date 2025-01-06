#pragma once

#include "gui/components/SmallGauge.h"
#include "gui/panels/Panel.h"

class EgtPanel : public Panel {

public:
    EgtPanel();
    virtual ~EgtPanel();

    void draw() override;

private:
    void updateValues();

private:
};