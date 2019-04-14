#include "display.h"

const std::array<uint8_t, 10> Display::leds = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

void Display::initPins()
{
    // initialize the LED pins
    for (uint8_t index = 0; index < leds.size(); index++)
    {
        pinMode(leds[index], OUTPUT);
    }
}

const Symbol& getSymbol(char sym)
{
    const Symbol* symbol;
    switch(sym)
    {
        case 'A':
        {
            symbol = &Symbols::symA;
            break;
        }

        case 'B':
        {
            symbol = &Symbols::symB;
            break;
        }

        case 'C':
        {
            symbol = &Symbols::symC;
            break;
        }

        case 'D':
        {
            symbol = &Symbols::symD;
            break;
        }

        case 'E':
        {
            symbol = &Symbols::symE;
            break;
        }

        case 'F':
        {
            symbol = &Symbols::symF;
            break;
        }

        case 'G':
        {
            symbol = &Symbols::symG;
            break;
        }

        case 'H':
        {
            symbol = &Symbols::symH;
            break;
        }

        case 'I':
        {
            symbol = &Symbols::symI;
            break;
        }

        case 'J':
        {
            symbol = &Symbols::symJ;
            break;
        }

        case 'K':
        {
            symbol = &Symbols::symK;
            break;
        }

        case 'L':
        {
            symbol = &Symbols::symL;
            break;
        }

        case 'M':
        {
            symbol = &Symbols::symM;
            break;
        }

        case 'N':
        {
            symbol = &Symbols::symN;
            break;
        }

        case 'O':
        {
            symbol = &Symbols::symO;
            break;
        }

        case 'P':
        {
            symbol = &Symbols::symP;
            break;
        }

        case 'R':
        {
            symbol = &Symbols::symR;
            break;
        }

        case 'S':
        {
            symbol = &Symbols::symS;
            break;
        }

        case 'T':
        {
            symbol = &Symbols::symT;
            break;
        }

        case 'U':
        {
            symbol = &Symbols::symU;
            break;
        }

        case 'V':
        {
            symbol = &Symbols::symV;
            break;
        }

        case 'W':
        {
            symbol = &Symbols::symW;
            break;
        }

        case 'X':
        {
            symbol = &Symbols::symX;
            break;
        }

        case '1':
        {
            symbol = &Symbols::symOne;
            break;
        }

        case '2':
        {
            symbol = &Symbols::symTwo;
            break;
        }

        case '3':
        {
            symbol = &Symbols::symThree;
            break;
        }

        case '4':
        {
            symbol = &Symbols::symFour;
            break;
        }

        case '5':
        {
            symbol = &Symbols::symFive;
            break;
        }

        case '6':
        {
            symbol = &Symbols::symSix;
            break;
        }

        case '7':
        {
            symbol = &Symbols::symSeven;
            break;
        }

        case '8':
        {
            symbol = &Symbols::symEight;
            break;
        }

        case '9':
        {
            symbol = &Symbols::symNine;
            break;
        }

        case '0':
        {
            symbol = &Symbols::symZero;
            break;
        }

        case '!':
        {
            symbol = &Symbols::symExclamation;
            break;
        }

        case '?':
        {
            symbol = &Symbols::symQuestion;
            break;
        }

        case '.':
        {
            symbol = &Symbols::symDot;
            break;
        }

        case ',':
        {
            symbol = &Symbols::symComma;
            break;
        }

        case ':':
        {
            symbol = &Symbols::symColon;
            break;
        }

        case ';':
        {
            symbol = &Symbols::symSemicolon;
            break;
        }

        default:
        {
            symbol = &Symbols::symUnsupported;
            break;
        }
    }
    return *symbol;
}