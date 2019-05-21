#include <interrupt.h>

#include <string>

#include "common.h"

#include "button.h"
#include "buttons.h"
#include "display.h"

HelloWorldButton helloWorldButton(BUTTON_1);
VictorButton victorButton(BUTTON_2);
RaduButton raduButton(BUTTON_3);

volatile int8_t hallState = 0;
volatile int32_t lastRotationStart = 0;
volatile int32_t lastRotationDuration = 0;

int timesToWait = 20;

void setup()
{
    if (DEBUG)
        Serial.begin(9600);

    Display::init();

    pinMode(helloWorldButton.pin, INPUT_PULLUP);
    pinMode(victorButton.pin, INPUT_PULLUP);
    pinMode(raduButton.pin, INPUT_PULLUP);
    pinMode(HALL_SENSOR, INPUT);

    hallState = !digitalRead(HALL_SENSOR); // establish the initial state, which can be 1 if the magnet is stopped near the sensor
    LOG_DEBUG("Initial hall state: %d", hallState);

    attachInterrupt(helloWorldButton.pin, ISRButtonHelloWorld, CHANGE);
    attachInterrupt(victorButton.pin, ISRButtonVictor, CHANGE);
    attachInterrupt(raduButton.pin, ISRButtonRadu, CHANGE);
    attachInterrupt(HALL_SENSOR, ISRHall, CHANGE);

    Display::setBufferIndex(0);
    // Display::submitString("DADA");
    // Display::submitString("DADA");
    // Display::submitString("DADA");
    Display::submitString("Hello World!", 0);
    Display::submitString("Victor Rusu", 1);
    Display::submitString("Radu Deleanu", 2);
}

void loop()
{
    // uint32_t start = micros();

    // // LOG_DEBUG("Hall state: ");
    // // LOG_DEBUG(hallState);

    // Display::onStartRotation(50000);
    // uint32_t waitTime = micros() - start;

    // // delay(5000);

    // delayMicroseconds(waitTime);
}

void ISRButtonHelloWorld()
{
    helloWorldButton.onStateChange();
}

void ISRButtonVictor()
{
    victorButton.onStateChange();
}

void ISRButtonRadu()
{
    raduButton.onStateChange();
}

void ISRHall()
{
    hallState = !hallState;
    // LOG_DEBUG("Hall state update: %d", hallState);
    if (!hallState) // hallState is now 0, new rotation
    {
        LOG_DEBUG("Magnet detected!");
        
        // float shit = (float)60000/(float)(lastRotationDuration/1000.0f);
        // std::string rotationString = std::to_string(shit);
        
        // Display::submitString(rotationString, true, 0); //rpm
        
        lastRotationDuration = micros() - lastRotationStart;
        lastRotationStart = micros();

        //TODO uncomment
        // if (lastRotationDuration < 62500) // ~1000rpm, 16rps, 62.5ms, 62500 us - in order to achieve persistence of vision
        // if (lastRotationDuration < 30000) // ~1000rpm, 16rps, 62.5ms, 62500 us - in order to achieve persistence of vision
            Display::onStartRotation(lastRotationDuration);
    }
}
