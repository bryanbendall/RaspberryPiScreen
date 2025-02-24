#include "CenterWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include <fmt/format.h>
#include <iostream>
#include <rlgl.h>

CenterWindow::CenterWindow()
    : m_touchInput(m_width, m_height)
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(m_height, m_width, "Center Window", flags);

    TouchInput::setActiveContext(&m_touchInput);

    int windowStatus = SetActiveWindowContext(m_windowID);
    if (windowStatus < 0)
        return;

#ifdef PC_BUILD
    SetWindowPosition(200, 560);
#endif
}

CenterWindow::~CenterWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void CenterWindow::draw()
{
    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

    m_touchInput.pollTouchEvents();

    BeginDrawing();
    rlPushMatrix();
    rlTranslatef(1280.0f, 0.0f, 0.0f);
    rlRotatef(90.0f, 0.0f, 0.0f, 1.0f);

    ClearBackground(GetColor(GlobalOutputs::black));

    // Selected Screen
    switch (m_currentScreen) {

    case Screens::Info:
        Ui::Text({ 400, 50 }, "Info", 100);
        break;

    case Screens::Map:
        Ui::Text({ 400, 50 }, "Map", 100);
        break;

    case Screens::Hvac: {

        Ui::Text({ 400.0f, 100.0f }, "Hvac", 100);

        Ui::SmallGauge({ 220.0f, 330.0f }, 250.0f, "Press", "battery.svg", GlobalOutputs::acPress, 0.0f, 500.0f);
        Ui::SmallGauge({ 580.0f, 330.0f }, 250.0f, "Vent", "battery.svg", GlobalOutputs::ventTemp, 0.0f, 100.0f);

        {
            Ui::Text({ 220.0f, 550.0f }, "Clutch On", 50);

            if (Ui::Button("-", { 120.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                GlobalInputs::acOnTemp -= 1.0f;

            std::string lable = fmt::format("{:.0f}", GlobalInputs::acOnTemp);
            Ui::Text({ 220.0f, 625.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 320.0f - 50.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                GlobalInputs::acOnTemp += 1.0f;
        }

        {
            Color c = GlobalOutputs::acClutchStatus ? GetColor(GlobalOutputs::green) : GetColor(GlobalOutputs::gray);
            Ui::Indicator({ 360.0f, 560.0f }, 80, "circle.svg", 1.0f, c);
        }

        {
            Ui::Text({ 580.0f, 550.0f }, "Clutch Off", 50);

            if (Ui::Button("-", { 480.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                GlobalInputs::acOffTemp -= 1.0f;

            std::string lable = fmt::format("{:.0f}", GlobalInputs::acOffTemp);
            Ui::Text({ 580.0f, 625.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 680.0f - 50.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                GlobalInputs::acOffTemp += 1.0f;
        }

        {
            Ui::Text({ 400.0f, 760.0f }, "Fan", 50);

            if (Ui::Button("Off", { 200.0f - 30.0f, 800.0f, 100.0f, 80.0f }, 40, false, GlobalInputs::hvacFan == 0.0f))
                GlobalInputs::hvacFan = 0.0f;
            if (Ui::Button("Lo", { 300.0f - 10.0f, 800.0f, 100.0f, 80.0f }, 40, false, GlobalInputs::hvacFan == 1.0f))
                GlobalInputs::hvacFan = 1.0f;
            if (Ui::Button("Med", { 400.0f + 10.0f, 800.0f, 100.0f, 80.0f }, 40, false, GlobalInputs::hvacFan == 2.0f))
                GlobalInputs::hvacFan = 2.0f;
            if (Ui::Button("Hi", { 500.0f + 30.0f, 800.0f, 100.0f, 80.0f }, 40, false, GlobalInputs::hvacFan == 3.0f))
                GlobalInputs::hvacFan = 3.0f;
        }

        if (Ui::Button("A/C Enable", { 300.0f, 930.0f, 200.0f, 80.0f }, 40, false, GlobalInputs::acEnable > 0.0f))
            GlobalInputs::acEnable > 0.0f ? GlobalInputs::acEnable = 0.0f : GlobalInputs::acEnable = 1.0f;

        {
            if (Ui::Button("Defrost", { 100.0f - 30.0f, 1060.0f, 150.0f, 80.0f }, 40, false, GlobalInputs::hvacLevel == 0.0f))
                GlobalInputs::hvacLevel = 0.0f;
            if (Ui::Button("Dash", { 250.0f - 10.0f, 1060.0f, 150.0f, 80.0f }, 40, false, GlobalInputs::hvacLevel == 1.0f))
                GlobalInputs::hvacLevel = 1.0f;
            if (Ui::Button("Bi Level", { 400.0f + 10.0f, 1060.0f, 150.0f, 80.0f }, 40, false, GlobalInputs::hvacLevel == 2.0f))
                GlobalInputs::hvacLevel = 2.0f;
            if (Ui::Button("Floor", { 550.0f + 30.0f, 1060.0f, 150.0f, 80.0f }, 40, false, GlobalInputs::hvacLevel == 3.0f))
                GlobalInputs::hvacLevel = 3.0f;
        }

        break;
    }

    case Screens::Settings:
        Ui::Text({ 400, 50 }, "Settings", 100);
        break;
    }

    // Nav Buttons
    if (Ui::Button("Info", { 33, 1180, 150, 100 }, 38, false, m_currentScreen == Screens::Info))
        m_currentScreen = Screens::Info;
    if (Ui::Button("Map", { 150 + 66, 1180, 150, 100 }, 38, false, m_currentScreen == Screens::Map))
        m_currentScreen = Screens::Map;
    if (Ui::Button("Hvac", { 300 + 99, 1180, 150, 100 }, 38, false, m_currentScreen == Screens::Hvac))
        m_currentScreen = Screens::Hvac;
    if (Ui::Button("Settings", { 450 + 132, 1180, 150, 100 }, 38, false, m_currentScreen == Screens::Settings))
        m_currentScreen = Screens::Settings;

    rlPopMatrix();
    EndDrawing();
}
