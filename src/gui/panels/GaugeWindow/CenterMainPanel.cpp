#include "CenterMainPanel.h"

#include "data/GlobalOutputs.h"
#include <raylib.h>

CenterMainPanel::CenterMainPanel()
    : m_boost({ 310.0f, 0.0f })
    , m_closedLoop({ 820.0f, 0.0f })
    , m_tach({ 640.0f, 240.0f }, 450.0f)
    , m_speedometer({ 640.0f, 240.0f })
    , m_afrGauge({ 640.0f, 120.0f })
    , m_leftTurn({ 640.0f - 200.0f, 5.0f }, 50, "left-turn-signal.svg", GetColor(GlobalOutputs::green))
    , m_rightTurn({ 640.0f + 150.0f, 5.0f }, 50, "right-turn-signal.svg", GetColor(GlobalOutputs::green))
    , m_gearIndicator({ 760.0f, 300.0f }, 120)

{
}

CenterMainPanel::~CenterMainPanel()
{
}

void CenterMainPanel::draw(int width, int height)
{
    updateValues();

    m_boost.draw();
    m_closedLoop.draw();
    m_tach.draw();
    m_speedometer.draw();
    m_afrGauge.draw();
    m_leftTurn.draw();
    m_rightTurn.draw();
    m_gearIndicator.draw();
}

void CenterMainPanel::updateValues()
{
    m_boost.setValue(GlobalOutputs::boost);
    m_closedLoop.setValue(GlobalOutputs::closedLoopComp);
    m_tach.setValue(GlobalOutputs::rpm);
    m_speedometer.setValue(GlobalOutputs::speed);
    m_speedometer.setKph(GlobalOutputs::useKph > 0.0001f);
    m_afrGauge.setValue(0, GlobalOutputs::afr);
    m_afrGauge.setValue(1, GlobalOutputs::afr2);
    m_afrGauge.setShowBoth(GlobalOutputs::showSecondAfr);
    m_leftTurn.setValue(GlobalOutputs::leftTurn);
    m_rightTurn.setValue(GlobalOutputs::rightTurn);
    m_gearIndicator.setValue(GlobalOutputs::gear);
}