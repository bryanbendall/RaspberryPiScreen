#pragma once

#include "gui/components/RemoteCamera.h"
#include "gui/panels/Panel.h"

class RightMapPanel : public Panel {

public:
    RightMapPanel();
    virtual ~RightMapPanel();

    void draw() override;

private:
    void updateValues();

private:
    RemoteCamera m_camera;
};