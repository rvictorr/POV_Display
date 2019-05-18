#ifndef BUTTONS_H
#define BUTTONS_H

#include "button.h"
#include "display.h"
#include "common.h"

class HelloWorldButton : public Button
{
public:
    HelloWorldButton(const uint8_t pin) : Button(pin) {}
    void onStateChange() override
    {
        Button::onStateChange();

        if (!isDown())
            return;
            
        LOG_DEBUG("Button Hello World clicked!")
        Display::setBufferIndex(0);
    }
};

class VictorButton : public Button
{
public:
    VictorButton(const uint8_t pin) : Button(pin) {}
    void onStateChange() override
    {
        Button::onStateChange();

        if (!isDown())
            return;

        LOG_DEBUG("Button Victor clicked!")
        Display::setBufferIndex(1);
    }
};

class RaduButton : public Button
{
public:
    RaduButton(const uint8_t pin) : Button(pin) {}
    void onStateChange() override
    {
        Button::onStateChange();

        if (!isDown())
            return;
            
        LOG_DEBUG("Button Radu Deleanu clicked!")
        Display::setBufferIndex(2);
    }
};

#endif