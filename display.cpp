#include "display.h"

uint8_t Display::persist = true;
uint16_t Display::delta = 0;
uint16_t Display::degree = 0;
uint16_t Display::startPos = 0;
std::vector<SymbolString> Display::buffer = {};
const std::array<uint8_t, 10> Display::leds = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

void ISRTimer()
{
    Display::onTimerOverflow();
}