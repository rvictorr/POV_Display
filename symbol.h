#define SYMBOL_HEIGHT 10

struct Symbol
{
    Symbol(const uint16_t* data, uint8_t width, uint8_t height = SYMBOL_HEIGHT) : data(data), width(width), height(height) {}
    const uint16_t* data;
    uint8_t width, height;
};