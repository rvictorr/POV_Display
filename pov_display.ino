#include <interrupt.h>

#include <string>

#include "common.h"

#include "button.h"
#include "buttons.h"
#include "display.h"

// Button buttonStart(BUTTON_START);
HelloWorldButton helloWorldButton(BUTTON_1);
VictorButton victorButton(BUTTON_2);
RaduButton raduButton(BUTTON_3);

volatile int8_t hallState = 0;
volatile int32_t lastRotationStart = 0;
volatile int32_t lastRotationDuration = 0;

int timesToWait = 20;

void setup()
{
    Serial.begin(9600);

    Display::init();

    // pinMode(buttonStart.pin, INPUT_PULLUP);
    pinMode(helloWorldButton.pin, INPUT_PULLUP);
    pinMode(victorButton.pin, INPUT_PULLUP);
    pinMode(raduButton.pin, INPUT_PULLUP);
    pinMode(HALL_SENSOR, INPUT);
    pinMode(1, OUTPUT);

    hallState = !digitalRead(HALL_SENSOR); // establish the initial state, which can be 1 if the magnet is stopped near the sensor
    LOG_DEBUG("Initial hall state: %d", hallState);

    // attachInterrupt(buttonStart.pin, ISRButtonStart, CHANGE);
    attachInterrupt(helloWorldButton.pin, ISRButtonHelloWorld, CHANGE);
    attachInterrupt(victorButton.pin, ISRButtonVictor, CHANGE);
    attachInterrupt(raduButton.pin, ISRButtonRadu, CHANGE);
    attachInterrupt(HALL_SENSOR, ISRHall, CHANGE);

    // digitalWrite(1, HIGH); // output 5V for the Hall sensor on pin 1
    // digitalWrite(A5, HIGH); // output 5V for the buttons on pin A5

    // Display::submitString("A   B   C   D   ");
    // Display::submitString("    .    .    .");
    Display::setBufferIndex(0);
    Display::submitString("DADA");
    Display::submitString("DADA");
    Display::submitString("DADA");
    // Display::submitString("Hello World!", 0);
    // Display::submitString("Victor Rusu", 1);
    // Display::submitString("Radu Deleanu", 2);
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

void ISRButtonStart()
{
    // buttonStart.onStateChange();
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
    LOG_DEBUG("Hall state update: %d", hallState);
    if (!hallState) // hallState is now 0, new rotation
    {
        // Display::submitString(std::to_string((float)60000/(float)(lastRotationDuration/1000.0f)), true, 0); //rps
        LOG_DEBUG("Magnet detected!");
        lastRotationDuration = micros() - lastRotationStart;
        lastRotationStart = micros();

        //TODO uncomment
        // if (lastRotationDuration < 62500) // ~1000rpm, 16rps, 62.5ms, 62500 us - in order to achieve persistence of vision
            Display::onStartRotation(lastRotationDuration); // TODO: uncomment after fixing the wiring
    }
}
