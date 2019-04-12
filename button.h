
class Button
{
public:
    Button(uint8_t pin) : pin(pin), state(0) {}
    inline int8_t isDown()
    {
        return state;
    }
    inline int8_t isHeld()
    {
        return state && (millis() - start > 750);
    }
    inline void onStateChange()
    {
        state = !state;
        start = millis();
    }
public:
    volatile int8_t state;
    volatile long start; 
    int8_t pin;
};
