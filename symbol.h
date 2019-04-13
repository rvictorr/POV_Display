struct Symbol
{
    Symbol(const uint16_t* data, uint8_t width, uint8_t height) : data(data), width(width), height(height) {}
    const uint16_t* data;
    uint8_t width, height;
};