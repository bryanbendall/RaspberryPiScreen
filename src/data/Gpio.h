#pragma once

class Gpio {

public:
    enum class PinState {
        Low = 0,
        High
    };

    static void writePin(int pin, PinState state);
    static void shutdown();

private:
    static void init();
};