#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button(uint8_t pin) : pin(pin), state(0) {}
    inline uint8_t isDown()
    {
        return state;
    }
    inline uint8_t isHeldDown()
    {
        return state && (millis() - start > 750);
    }
    inline void onStateChange()
    {
        state = !state;
        start = millis();
    }

public:
    volatile uint8_t state;
    volatile long start;
    uint8_t pin;
};

#endif