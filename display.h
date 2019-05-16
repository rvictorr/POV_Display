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

    static void setPersist(uint8_t shouldPersist);
    static void onStartRotation(uint16_t lastRotationDuration);
    static void onTimerOverflow();
    static void submitString(const std::string &string, uint8_t centered);

private:
    Display();
    static void writeBuffer();
    static void writeString(const SymbolString& toWrite);
    static void writeSymbol(const Symbol *symbol);
    static void writeColumn(uint16_t pattern);
    static void calculateStartPosition(const SymbolString& symString, uint8_t centered);

private:
    static const std::array<uint8_t, 10> leds; // later maybe convert the length to a template argument

    static uint8_t persist;
    static uint16_t degree;
    static uint16_t delta;
    static uint16_t startPos;
    static std::vector<SymbolString> buffer;
};

inline void Display::onStartRotation(uint16_t lastRotationDuration)
{
    // setup timer here
    degree = lastRotationDuration / 360;
    delta = degree / 4; // resolution = 0.25 degrees
    
    LOG_DEBUG("onStartRotation, lastRotationDuration = %d, degree = %d, delta = %d, startPos = %d", lastRotationDuration, degree, delta, startPos);

    Display::writeBuffer();

    LOG_DEBUG("TIMER INITIALIZED");
}

inline void Display::onTimerOverflow()
{
    // start drawing
    LOG_DEBUG("Timer overflow");
    // Timer1.stop();
    Display::writeBuffer();
}

inline void Display::submitString(const std::string &string, uint8_t centered = true)
{
    LOG_DEBUG("Submitting string %s", string.c_str());

    SymbolString symString(string, centered);
    buffer.emplace_back(symString);

    // calculate where to start drawing
    // baseline is 120 degrees
    if (delta != 0)
        calculateStartPosition(symString, centered);
}

inline void Display::writeBuffer() // doesn't work properly yet
{
    if (buffer.size() == 0)
    {
        writeColumn(0); // clear the display
        return;
    }

    for (auto toWrite : buffer)
    {
        Display::writeString(toWrite);

        if (!persist)
        {    
            // pop the string that was drawn on the display
            buffer.pop_back();
        }
    }
}

inline void Display::writeString(const SymbolString& toWrite)
{    
    LOG_DEBUG("writeString called");

    if (startPos == 0)
        calculateStartPosition(toWrite, toWrite.centered);

    // Timer1.initialize(startPos); // piece of shit
    delayMicroseconds(startPos); // TODO: might need to compensate for the time spent executing the above instructions

    for (const auto *symbol : toWrite.elements)
    {
        Display::writeSymbol(symbol);
        delayMicroseconds((uint16_t)floor(delta * 3)); // character spacing
    }
}

inline void Display::writeSymbol(const Symbol *symbol)
{
    for (uint8_t index = 0; index < symbol->width; index++)
    {
        Display::writeColumn(symbol->data[index]);
        delayMicroseconds((uint16_t)floor(delta));
        // delay(delta*3); // for testing purposes
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

inline void Display::calculateStartPosition(const SymbolString& symString, uint8_t centered)
{
    startPos = centered ? (180 * degree - (int16_t)(symString.width * delta / 2)) : 120 * degree;
}

inline void Display::setPersist(uint8_t shouldPersist)
{
    persist = shouldPersist;
}

#endif