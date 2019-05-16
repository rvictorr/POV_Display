#ifndef SYMBOL_H
#define SYMBOL_H

#include "common.h"

#define SYMBOL_HEIGHT 10

struct Symbol
{
    Symbol() : Symbol({}, 0) {}
    Symbol(const uint16_t *data, uint8_t width, uint8_t height = SYMBOL_HEIGHT) : data(data), width(width), height(height) {}
    const uint16_t *data;
    uint8_t width, height;
};

const Symbol *getSymbol(char sym);

#endif