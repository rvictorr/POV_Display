#ifndef DISPLAY_H
#define DISPLAY_H

#include <array>
#include <vector>
#include <cmath>

#include <Arduino.h>

#include "common.h"
#include "constants.h"
#include "symbolstring.h"

const Symbol *getSymbol(char sym);

void ISRTimer();

class Display
{
public:
    static void init()
    {
        // Timer1.attachInterrupt(ISRTimer); //piece of shit
        // initialize the LED pins
        for (uint8_t index = 0; index < leds.size(); index++)
        {
            pinMode(leds[index], OUTPUT);
        }
    }

    // TESTING BUFFERS
    static void onStartRotation(uint16_t lastRotationDuration);
    static void onTimerOverflow();
    static void submitString(const std::string &string, uint8_t centered);

private:
    Display();
    static void writeString();
    static void writeSymbol(const Symbol *symbol);
    static void writeColumn(uint16_t pattern);

private:
    static const std::array<uint8_t, 10> leds; // later maybe convert the length to a template argument

    static uint16_t degree;
    static uint16_t delta;
    static uint16_t startPos;
    // static std::vector<const Symbol *> buffer;
    static std::vector<SymbolString> buffer;
};

inline void Display::onStartRotation(uint16_t lastRotationDuration)
{
    // setup timer here
    degree = lastRotationDuration / 360;
    delta = degree / 4; // resolution = 0.25 degrees
    
    // LOG_DEBUG("onStartRotation, lastRotationDuration = %d, degree = %d, delta = %d, startPos = %d", lastRotationDuration, degree, delta, startPos);

    if (startPos != 0) // startPos is initialized
    {
        // Timer1.initialize(startPos); // piece of shit
        delayMicroseconds(startPos);
        Display::writeString();

        // LOG_DEBUG("TIMER INITIALIZED");
    }
}

inline void Display::onTimerOverflow()
{
    // start drawing
    LOG_DEBUG("Timer overflow");
    // Timer1.stop();
    Display::writeString();
}

inline void Display::submitString(const std::string &string, uint8_t centered = true)
{
    LOG_DEBUG("Submitting string %s", string.c_str());

    SymbolString symString(string);
    buffer.emplace_back(symString);

    uint16_t width = symString.width * delta; // width of the string, in time units
    
    LOG_DEBUG("string width = %d", width);

    // calculate where to start drawing
    // baseline is 120 degrees
    startPos = centered ? (180 * degree - (int16_t)width / 2) : 120 * degree;
}

inline void Display::writeString()
{
    if (buffer.size() == 0)
        return;
    
    LOG_DEBUG("writeString called");

    const SymbolString& toWrite = buffer.back();

    for (const auto *symbol : toWrite.elements)
    {
        Display::writeSymbol(symbol);
        delayMicroseconds((uint16_t)floor(delta * 3)); // character spacing
    }

    // pop the string that was written
    buffer.pop_back();
}

inline void Display::writeSymbol(const Symbol *symbol)
{
    for (uint8_t index = 0; index < symbol->width; index++)
    {
        Display::writeColumn(symbol->data[index]);
        delayMicroseconds((uint16_t)floor(delta));
        // LOG_DEBUG("index = %d, delta = %d", index, delta);
    }
}

inline void Display::writeColumn(uint16_t pattern)
{
    uint8_t len = leds.size();
    for (uint8_t index = 0; index < len; index++) // writes LSB -> MSB
    {
        uint8_t value = (pattern & (1 << index)) >> index;
        digitalWrite(leds[index], value);
        //LOG_DEBUG("value = ");
        //LOG_DEBUG(value, BIN);
    }
}

#endif