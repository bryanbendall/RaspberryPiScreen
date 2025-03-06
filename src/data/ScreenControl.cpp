#include "ScreenControl.h"

#include "data/GlobalOutputs.h"
#include "data/Gpio.h"

void ScreenControl::update()
{
    updateScreen(m_screen1, GlobalOutputs::screen1);
    updateScreen(m_screen2, GlobalOutputs::screen2);
}

void ScreenControl::updateScreen(Screen& screen, float globalVariable)
{
    screen.desiredState = globalVariable > 0.5f;

    if (screen.desiredState != screen.state) {
        Gpio::writePin(screen.pin, Gpio::PinState::Low);
        screen.pinPulse = true;
        screen.state = screen.desiredState;
        return;
    }

    // Clear pulse on next update
    if (screen.pinPulse){
        Gpio::writePin(screen.pin, Gpio::PinState::High);
        screen.pinPulse = false;
    }
}