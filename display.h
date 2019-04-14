#include <array>
#include <Arduino.h>

#include "constants.h"

class Display
{
public:
    static void initPins();
    static void writeSymbol(char symbol);
    inline static void writeColumn(uint16_t pattern)
    {
        uint8_t len = leds.size();
        for (uint8_t index = 0; index  < len; index++) // writes LSB -> MSB
        {
            uint8_t value = (pattern & (1 << index)) >> index;
            digitalWrite(leds[index], value);
            //LOG_DEBUG("value = ");
            //LOG_DEBUG(value, BIN);
        }
    }
private:
    Display();
private:
    const static std::array<uint8_t, 10> leds;
};

const Symbol& getSymbol(char sym);

inline void Display::writeSymbol(char symbol)
{
    const Symbol& toWrite = getSymbol(symbol);
    // TODO implement logic
    
}