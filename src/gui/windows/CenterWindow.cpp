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

    case Screens::Info: {
        Ui::Text({ 400.0f, 100.0f }, "Info", 100);

        Ui::Text({ 400.0f, 300.0f }, "Meth Afr", 60, GetColor(GlobalOutputs::gray));
        std::string lable = fmt::format("{:.1f}", GlobalOutputs::values["methAfr"]);
        Ui::Text({ 400.0f, 360.0f }, lable, 60);

        break;
    }

    case Screens::Map:
        Ui::Text({ 400.0f, 100.0f }, "Map", 100);
        break;

    case Screens::Hvac: {

        Ui::Text({ 400.0f, 100.0f }, "Hvac", 100);

        Ui::SmallGaugeSpec acPressSpec {};
        acPressSpec.value = GlobalOutputs::values["acPress"];
        acPressSpec.center = { 220.0f, 330.0f };
        acPressSpec.size = 250.0f;
        acPressSpec.label = "Press";
        acPressSpec.max = 500.0f;
        Ui::SmallGauge(acPressSpec);

        Ui::SmallGaugeSpec acTempSpec {};
        acTempSpec.value = GlobalOutputs::values["acCoreTemp"];
        acTempSpec.center = { 580.0f, 330.0f };
        acTempSpec.size = 250.0f;
        acTempSpec.label = "Temp";
        acTempSpec.iconFilename = "water-temp.svg";
        Ui::SmallGauge(acTempSpec);

        {
            float& acOnTemp = GlobalInputs::values["acOnTemp"];

            Ui::Text({ 220.0f, 550.0f }, "Clutch On", 50);

            if (Ui::Button("-", { 120.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                acOnTemp -= 1.0f;

            std::string lable = fmt::format("{:.0f}", acOnTemp);
            Ui::Text({ 220.0f, 625.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 320.0f - 50.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                acOnTemp += 1.0f;
        }

        {
            Color c = GlobalOutputs::values["acClutchStatus"] ? GetColor(GlobalOutputs::green) : GetColor(GlobalOutputs::gray);
            Ui::Indicator({ 360.0f, 560.0f }, 80, "circle.svg", 1.0f, c);
        }

        {
            float& acOffTemp = GlobalInputs::values["acOffTemp"];

            Ui::Text({ 580.0f, 550.0f }, "Clutch Off", 50);

            if (Ui::Button("-", { 480.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                acOffTemp -= 1.0f;

            std::string lable = fmt::format("{:.0f}", acOffTemp);
            Ui::Text({ 580.0f, 625.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 680.0f - 50.0f, 600.0f, 50.0f, 50.0f }, 30, true))
                acOffTemp += 1.0f;
        }

        {
            float& hvacFan = GlobalInputs::values["hvacFan"];

            Ui::Text({ 400.0f, 760.0f }, "Fan", 50);

            if (Ui::Button("Off", { 200.0f - 30.0f, 800.0f, 100.0f, 80.0f }, 40, false, hvacFan == 0.0f))
                hvacFan = 0.0f;
            if (Ui::Button("Lo", { 300.0f - 10.0f, 800.0f, 100.0f, 80.0f }, 40, false, hvacFan == 1.0f))
                hvacFan = 1.0f;
            if (Ui::Button("Med", { 400.0f + 10.0f, 800.0f, 100.0f, 80.0f }, 40, false, hvacFan == 2.0f))
                hvacFan = 2.0f;
            if (Ui::Button("Hi", { 500.0f + 30.0f, 800.0f, 100.0f, 80.0f }, 40, false, hvacFan == 3.0f))
                hvacFan = 3.0f;
        }

        {
            float& acEnable = GlobalInputs::values["acEnable"];

            if (Ui::Button("A/C Enable", { 300.0f, 930.0f, 200.0f, 80.0f }, 40, false, acEnable > 0.0f))
                acEnable > 0.0f ? acEnable = 0.0f : acEnable = 1.0f;
        }

        {
            float& hvacLevel = GlobalInputs::values["hvacLevel"];

            if (Ui::Button("Defrost", { 100.0f - 30.0f, 1060.0f, 150.0f, 80.0f }, 40, false, hvacLevel == 0.0f))
                hvacLevel = 0.0f;
            if (Ui::Button("Dash", { 250.0f - 10.0f, 1060.0f, 150.0f, 80.0f }, 40, false, hvacLevel == 1.0f))
                hvacLevel = 1.0f;
            if (Ui::Button("Bi Level", { 400.0f + 10.0f, 1060.0f, 150.0f, 80.0f }, 40, false, hvacLevel == 2.0f))
                hvacLevel = 2.0f;
            if (Ui::Button("Floor", { 550.0f + 30.0f, 1060.0f, 150.0f, 80.0f }, 40, false, hvacLevel == 3.0f))
                hvacLevel = 3.0f;
        }

        break;
    }

    case Screens::Settings:
        Ui::Text({ 400.0f, 100.0f }, "Settings", 100);

        float& methEnable = GlobalInputs::values["methEnable"];
        if (Ui::Button("Meth Enable", { 280.0f, 200.0f, 240.0f, 80.0f }, 40, false, methEnable > 0.0f))
            methEnable > 0.0f ? methEnable = 0.0f : methEnable = 1.0f;

        {
            float& baseBoost = GlobalInputs::values["baseBoost"];

            Ui::Text({ 400.0f, 350.0f }, "Base Boost", 40);

            if (Ui::Button("-", { 300.0f, 400.0f, 50.0f, 50.0f }, 30, true))
                baseBoost -= 1.0f;

            // Clamp bottom to 0
            if (baseBoost < 0.0f)
                baseBoost = 0.0f;

            std::string lable = fmt::format("{:.0f}", baseBoost);
            Ui::Text({ 400.0f, 425.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 500.0f - 50.0f, 400.0f, 50.0f, 50.0f }, 30, true))
                baseBoost += 1.0f;

            // Clamp top to 15
            if (baseBoost > 15.0f)
                baseBoost = 15.0f;
        }

        {
            float& maxBoost = GlobalInputs::values["maxBoost"];

            Ui::Text({ 400.0f, 500.0f }, "Max Boost", 40);

            if (Ui::Button("-", { 300.0f, 550.0f, 50.0f, 50.0f }, 30, true))
                maxBoost -= 1.0f;

            // Clamp bottom to 0
            if (maxBoost < 0.0f)
                maxBoost = 0.0f;

            std::string lable = fmt::format("{:.0f}", maxBoost);
            Ui::Text({ 400.0f, 575.0f }, lable.c_str(), 40);

            if (Ui::Button("+", { 500.0f - 50.0f, 550.0f, 50.0f, 50.0f }, 30, true))
                maxBoost += 1.0f;

            // Clamp top to 20
            if (maxBoost > 20.0f)
                maxBoost = 20.0f;
        }

        {
            float& primeGas = GlobalInputs::values["primeGas"];

            Rectangle gasRect = { 175.0f, 650.0f, 200.0f, 80.0f };
            Ui::Button("Prime Gas", gasRect, 40);

            TouchInput* touch = TouchInput::get();
            if (touch) {
                if (touch->isDown(gasRect))
                    primeGas = 1.0f;
                else
                    primeGas = 0.0f;
            }

            float& primeMeth = GlobalInputs::values["primeMeth"];

            Rectangle methRect = { 425.0f, 650.0f, 200.0f, 80.0f };
            Ui::Button("Prime Meth", methRect, 40);

            if (touch) {
                if (touch->isDown(methRect))
                    primeMeth = 1.0f;
                else
                    primeMeth = 0.0f;
            }
        }

        float& useKph = GlobalInputs::values["useKph"];

        if (Ui::Button("Mph", { 200.0f, 800.0f, 200.0f, 80.0f }, 40, false, GlobalOutputs::values["useKph"] < 0.5f))
            useKph = 0.0f;
        if (Ui::Button("Kph", { 400.0f, 800.0f, 200.0f, 80.0f }, 40, false, GlobalOutputs::values["useKph"] > 0.5f))
            useKph = 1.0f;

        if (Ui::Button("Save", { 300.0f, 1000.0f, 200.0f, 80.0f }, 40, true))
            GlobalInputs::saveToFile();

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
