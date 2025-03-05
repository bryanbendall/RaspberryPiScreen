#include "Gpio.h"

#include <gpiod.h>
#include <stdio.h>

struct gpiod_chip* gpiochip;
struct gpiod_line* gpioline[28];

void Gpio::writePin(int pin, PinState state)
{
    if (pin >= 28)
        return;

    if (gpioline[pin] == nullptr) {

        if (gpiochip == nullptr)
            init();
        if (gpiochip == nullptr)
            return;

        gpioline[pin] = gpiod_chip_get_line(gpiochip, pin);
        if (gpioline[pin] == nullptr)
            return;

        gpiod_line_request_output(gpioline[pin], "ardEmul", 0);
    }

    gpiod_line_set_value(gpioline[pin], (int)state);
}

void Gpio::shutdown(){
    if (gpiochip != nullptr) {
        for (int loop = 0; loop < 28; loop++)
            if (gpioline[loop] != nullptr) {
                gpiod_line_release(gpioline[loop]);
                gpioline[loop] = nullptr;
            }
        gpiod_chip_close(gpiochip);
        gpiochip = nullptr;
    }
}

void Gpio::init()
{
    gpiochip = gpiod_chip_open_by_name("gpiochip4");

    if (gpiochip == nullptr)
        gpiochip = gpiod_chip_open_by_name("gpiochip0");

    if (gpiochip == nullptr) {
        printf("unable to open GPIO\n");
        return;
    }
    for (int loop; loop < 28; loop++)
        gpioline[loop] = nullptr;
    return;
}