#pragma once

#include "gui/components/RemoteCamera.h"
#include "gui/panels/Panel.h"

class RightMapPanel : public Panel {

public:
    RightMapPanel();
    virtual ~RightMapPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    RemoteCamera m_camera;
};