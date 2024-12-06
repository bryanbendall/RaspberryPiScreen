#include "GaugeWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Utils.h"
#include "gui/components/AfrGauge.h"
#include "gui/components/BarGauge.h"
#include "gui/components/BoostGauge.h"
#include "gui/components/ClosedLoopGauge.h"
#include "gui/components/GearIndicator.h"
#include "gui/components/Indicator.h"
#include "gui/components/SmallGauge.h"
#include "gui/components/Speedometer.h"
#include "gui/components/TachGauge.h"
#include <raylib.h>

BoostGauge boost({ 310.0f, 0.0f });

ClosedLoopGauge closedLoop({ 820.0f, 0.0f });

TachGauge tach({ 640.0f, 240.0f }, 450.0f, 10000.0f);

Speedometer speedometer({ 640.0f, 240.0f });

AfrGauge afrGauge({ 640.0f, 120.0f });

SmallGauge waterGauge({ 200.0f, 125.0f }, 150.0f, 30.0f, 250.0f, "°F", SmallGauge::Icon::WaterTemp);
SmallGauge oilGauge({ 200.0f, 325.0f }, 150.0f, 0.0f, 100.0f, "Psi", SmallGauge::Icon::Oil);

SmallGauge batteryGauge({ 1020.0f, 100.0f }, 150.0f, 6.0f, 18.0f, "V", SmallGauge::Icon::Battery);
SmallGauge transGauge({ 1190.0f, 100.0f }, 150.0f, 50.0f, 280.0f, "°F", SmallGauge::Icon::TransTemp);
SmallGauge gasGauge({ 1020.0f, 270.0f }, 150.0f, 0.0f, 100.0f, "Gas", SmallGauge::Icon::Fuel);
SmallGauge methGauge({ 1190.0f, 270.0f }, 150.0f, 0.0f, 100.0f, "Meth", SmallGauge::Icon::Fuel);

BarGauge gasLevel({ 1000.0f, 390.0f }, { 240.0f, 10.0f }, 0.0f, 100.0f);
BarGauge methLevel({ 1000.0f, 430.0f }, { 240.0f, 10.0f }, 0.0f, 100.0f);

Indicator leftTurn({ 640.0f - 200.0f, 5.0f }, 50, "../resources/images/left-turn-signal.svg", GetColor(GlobalOutputs::green));
Indicator rightTurn({ 640.0f + 150.0f, 5.0f }, 50, "../resources/images/right-turn-signal.svg", GetColor(GlobalOutputs::green));

Indicator parkingLight({ 30.0f, 30.0f }, 50, "../resources/images/low-beam.svg", GetColor(GlobalOutputs::orange));
Indicator lowBeam({ 30.0f, 30.0f }, 50, "../resources/images/low-beam.svg", GetColor(GlobalOutputs::green));
Indicator highBeam({ 30.0f, 30.0f }, 50, "../resources/images/high-beam.svg", GetColor(GlobalOutputs::blue));
Indicator fogLight({ 32.0f, 90.0f }, 45, "../resources/images/fog-lights.svg", GetColor(GlobalOutputs::green));
Indicator parkingBrake({ 30.0f, 150.0f }, 50, "../resources/images/parking-brake.svg", GetColor(GlobalOutputs::red));
Indicator fan({ 30.0f, 210.0f }, 50, "../resources/images/fan.svg", GetColor(GlobalOutputs::blue));
Indicator engineLight({ 30.0f, 270.0f }, 50, "../resources/images/engine-light.svg", GetColor(GlobalOutputs::orange));

GearIndicator gearIndicator({ 760.0f, 300.0f }, 120);

GaugeWindow::GaugeWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(1280.0f, 480.0f, "Gauge Window", flags);

    SetActiveWindowContext(m_windowID);
#ifdef PC_BUILD
    SetWindowPosition(200, 40);
#endif

    SmallGauge::initResources();
    BarGauge::initResources();
    tach.initResources();
    speedometer.initResources();
    afrGauge.initResources();
    boost.initResources();
    closedLoop.initResources();
    leftTurn.initResources();
    rightTurn.initResources();
    parkingLight.initResources();
    lowBeam.initResources();
    highBeam.initResources();
    fogLight.initResources();
    parkingBrake.initResources();
    fan.initResources();
    engineLight.initResources();
    gearIndicator.initResources();
}

GaugeWindow::~GaugeWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void GaugeWindow::draw()
{
    updateValues();

    if (IsKeyPressed(KEY_C))
        m_camera.open("http://192.168.1.190:8080/stream.mjpeg");
    if (IsKeyPressed(KEY_D))
        m_camera.close();

    if (IsKeyDown(KEY_L))
        GlobalInputs::button0 = 1.0f;
    else
        GlobalInputs::button0 = 0.0f;

    SetActiveWindowContext(m_windowID);

    m_camera.updateTexture();

    BeginDrawing();

    ClearBackground(GetColor(GlobalOutputs::black));

    boost.draw();

    closedLoop.draw();

    tach.draw();

    speedometer.draw();

    afrGauge.draw();

    waterGauge.draw();
    oilGauge.draw();

    batteryGauge.draw();
    transGauge.draw();
    gasGauge.draw();
    methGauge.draw();

    gasLevel.draw();
    methLevel.draw();

    leftTurn.draw();
    rightTurn.draw();

    parkingLight.draw();
    lowBeam.draw();
    highBeam.draw();
    fogLight.draw();
    parkingBrake.draw();
    fan.draw();
    engineLight.draw();

    gearIndicator.draw();

    if (m_camera.isOpen())
        DrawTexture(m_camera.getTexture(), 0, 0, WHITE);

    DrawFPS(0, 0);

#ifndef PC_BUILD
    DrawRectangleLines(0, 0, 1280, 480, WHITE);
#endif

    EndDrawing();
}

void GaugeWindow::updateValues()
{
    boost.setValue(GlobalOutputs::boost);

    closedLoop.setValue(GlobalOutputs::closedLoopComp);

    tach.setValue(GlobalOutputs::rpm);

    speedometer.setValue(GlobalOutputs::speed);
    speedometer.setKph(GlobalOutputs::useKph > 0.0001f);

    afrGauge.setValue(0, GlobalOutputs::afr);
    afrGauge.setValue(1, GlobalOutputs::afr2);
    afrGauge.setShowBoth(GlobalOutputs::showSecondAfr);

    waterGauge.setValue(GlobalOutputs::cts);
    oilGauge.setValue(GlobalOutputs::oilPressure);

    batteryGauge.setValue(GlobalOutputs::battery);
    transGauge.setValue(GlobalOutputs::lineTemp);
    gasGauge.setValue(GlobalOutputs::fuelPressure);
    methGauge.setValue(GlobalOutputs::methPressure);

    gasLevel.setValue(GlobalOutputs::gasLevel);
    methLevel.setValue(GlobalOutputs::methLevel);

    leftTurn.setValue(GlobalOutputs::leftTurn);
    rightTurn.setValue(GlobalOutputs::rightTurn);

    parkingLight.setValue(GlobalOutputs::parkingLights);
    lowBeam.setValue(GlobalOutputs::lowBeam);
    highBeam.setValue(GlobalOutputs::highBeam);
    fogLight.setValue(GlobalOutputs::fogLights);
    parkingBrake.setValue(GlobalOutputs::parkingBrake);
    fan.setValue(GlobalOutputs::fanState);
    engineLight.setValue(GlobalOutputs::engineLight);

    gearIndicator.setValue(GlobalOutputs::gear);
}