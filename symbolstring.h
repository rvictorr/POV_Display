#ifndef SYMBOLSTRING_H
#define SYMBOLSTRING_H

#include "common.h"
#include "symbol.h"

#include <string>
#include <vector>

struct SymbolString
{
    SymbolString() : elements(), width(0) {}
    SymbolString(const std::string& string, uint8_t centered = true) : cppString(string), centered(centered)
    {
        for (char c : cppString)
        {
            const Symbol* symbol = getSymbol(c);
            elements.push_back(symbol);
            width += symbol->width;
        }
    }
    SymbolString& operator=(const SymbolString& other) 
    {
        cppString = other.cppString;
        centered = other.centered;
        width = other.width;
        elements = other.elements;
        return *this;
    }
    
    void insert(const Symbol* symbol)
    {
        elements.push_back(symbol);
    }

    const std::string& toString()
    {
        return cppString;
    }

    std::vector<const Symbol*> elements;
    std::string cppString;
    uint8_t width;
    uint8_t centered;
};

#endif