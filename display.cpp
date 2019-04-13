#include "display.h"

const std::array<uint8_t, 10> Display::leds = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

void Display::initPins()
{
    // initialize the LED pins
    for (uint8_t index = 0; index < leds.size(); index++)
    {
        pinMode(leds[index], OUTPUT);
    }
}
