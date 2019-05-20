#include "display.h"

uint16_t Display::delta = 0;
uint16_t Display::degree = 0;
uint32_t Display::startPos = 0;

uint32_t Display::rotationStartMicros = 0;
uint32_t Display::timeLost = 0;

std::vector<SymbolString> Display::buffer = {};
uint8_t Display::bufferIndex = 0;
// const std::array<uint8_t, 10> Display::leds = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
const std::array<uint8_t, 10> Display::leds = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

void ISRTimer()
{
    Display::onTimerOverflow();
}