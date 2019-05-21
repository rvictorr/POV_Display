#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"

#include "constants.h"
#include "symbolstring.h"

#include <algorithm>
#include <array>
#include <vector>
#include <cmath>

const Symbol *getSymbol(char sym);

void ISRTimer();

class Display
{
public:
    static void init()
    {
        // Timer1.attachInterrupt(ISRTimer);
        // initialize the LED pins
        for (uint8_t index = 0; index < leds.size(); index++)
        {
            pinMode(leds[index], OUTPUT);
        }
    }

    static void onStartRotation(uint32_t lastRotationDuration);
    static void onTimerOverflow();
    static void submitString(const std::string &string, uint8_t centered, int8_t index);
    static void setBufferIndex(uint8_t index)
    {
        LOG_DEBUG("Setting buffer index to %d", index);
        if (bufferIndex < buffer.size())
            bufferIndex = index;
    }

private:
    Display();
    static void writeBuffer();
    static void writeString(const SymbolString& toWrite);
    static void writeSymbol(const Symbol *symbol);
    static void writeColumn(uint16_t pattern);
    static void calculateStartPosition(const SymbolString& symString, uint8_t centered);

private:
    static const std::array<uint8_t, 10> leds; // later maybe convert the length to a template argument

    static uint16_t degree;
    static uint16_t delta;
    static uint32_t startPos;
    static std::vector<SymbolString> buffer;
    static uint8_t bufferIndex;

    static uint32_t rotationStartMicros;
    static uint32_t timeLost;
};

inline void Display::onStartRotation(uint32_t lastRotationDuration)
{
    rotationStartMicros = micros();
    // setup timer here
    degree = lastRotationDuration / 360;
    delta = degree / 4; // resolution = 0.25 degrees
    
    // LOG_DEBUG("onStartRotation, lastRotationDuration = %d, degree = %d, delta = %d, startPos = %d", lastRotationDuration, degree, delta, startPos);

    // LOG_DEBUG("TIMER INITIALIZED");
    
    writeBuffer();
}

inline void Display::onTimerOverflow()
{
    // start drawing
    LOG_DEBUG("Timer overflow");
    // Timer1.stop();
    writeBuffer();
}

inline void Display::submitString(const std::string &string, uint8_t centered = true, int8_t index = -1)
{
    LOG_INFO("Submitting string %s at buffer index %d", string.c_str(), index);

    SymbolString symString(string, centered);

    if (buffer.size() > 5) // buffer capacity 5, probably temporary
        buffer.pop_back();

    if (index < 0)
        buffer.emplace_back(symString);
    else
    {
        auto it = buffer.begin() + index;
        *it = symString;
    }
}

inline void Display::writeBuffer() // doesn't work properly yet
{
    if (buffer.size() == 0)
    {
        writeColumn(0); // clear the display
        return;
    }

    writeString(buffer[bufferIndex]);

    writeColumn(0);
}

inline void Display::writeString(const SymbolString& toWrite)
{    
    // calculate where to start drawing
    // baseline is 120 degrees
    if (delta != 0)
        calculateStartPosition(toWrite, toWrite.centered);

    // Timer1.initialize(startPos);
    
    timeLost = micros() - rotationStartMicros;
    
    if (((int32_t)startPos - (int32_t)timeLost) > 0)
        startPos = startPos - timeLost;
    else
        startPos = 0; // start drawing immediately if we lose too much time

    LOG_DEBUG("Time lost: %d, new startPos: %d", timeLost, startPos);
    delayMicroseconds(startPos); // compensate for the time spent executing the above instructions

    // for (const auto *symbol : toWrite.elements)
    for (int8_t i = toWrite.elements.size() - 1; i >= 0; i--)
    {
        LOG_DEBUG("Crash test, char = %c, i = %d", toWrite.elements[i]->character, i);
        writeSymbol(toWrite.elements[i]);
        // writeSymbol(symbol);
        writeColumn(0);
        delayMicroseconds(delta * 3); // character spacing
    }
}

inline void Display::writeSymbol(const Symbol *symbol)
{
    for (int8_t index = symbol->width-1; index >= 0; index--)
    // for (uint8_t index = 0; index < symbol->width; index++)
    {
        Display::writeColumn(symbol->data[index]);
        delayMicroseconds(delta);
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
    startPos = centered ? (90 * degree - (int16_t)(symString.width * delta / 2)) : 30 * degree;
    // startPos = 30 * degree; //TODO: remove, temporary
}

#endif