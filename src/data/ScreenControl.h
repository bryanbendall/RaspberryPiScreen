#pragma once

class ScreenControl {

public:
    ScreenControl() = default;
    void update();

private:
struct Screen{
    int pin;
    bool state = true;
    bool desiredState = true;
    bool pinPulse = false;
};

void updateScreen(Screen& screen, float globalVariable);

Screen m_screen1 { 6 };
Screen m_screen2 { 5 };
};