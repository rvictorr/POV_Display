#include <interrupt.h>

#include "common.h"

#include "button.h"
#include "display.h"

Button buttonStart(BUTTON_START);
Button button1(BUTTON_1);
Button button2(BUTTON_2);
Button button3(BUTTON_3);

volatile int8_t hallState = 0;
//volatile int8_t timerState = 0;
//volatile int16_t timerPeriod = 0;
volatile int16_t lastRotationStart = 0;
volatile int16_t lastRotationDuration = 0;
//volatile int16_t minResolutionPeriod = 0;


int timesToWait = 10;

void setup()
{
    Serial.begin(9600);

    Display::init();

    //Display::setResolution(1500000);
    //Display::setResolution(2000.0f);

    pinMode(buttonStart.pin, INPUT_PULLUP);
    pinMode(button1.pin, INPUT_PULLUP);
    pinMode(button2.pin, INPUT_PULLUP);
    pinMode(button3.pin, INPUT_PULLUP);
    pinMode(HALL_SENSOR, INPUT);

    hallState = !digitalRead(HALL_SENSOR); // establish the initial state, which can be 1 if the magnet is stopped near the sensor

    attachInterrupt(buttonStart.pin, ISRButtonStart, CHANGE);
    attachInterrupt(button1.pin, ISRButton1, CHANGE);
    attachInterrupt(button2.pin, ISRButton2, CHANGE);
    attachInterrupt(button3.pin, ISRButton3, CHANGE);
    attachInterrupt(HALL_SENSOR, ISRHall, CHANGE);

    //Display::writeColumn(0b1111100000);
    //Display::submitString("A");
}

void loop()
{
    if (timesToWait == 0)
    {
        timesToWait = 10;
        Display::submitString("A");
    }
    //Display::writeSymbol('O');

    // LOG_DEBUG("-------START SERIAL-------\n");
    // LOG_DEBUG("Start button: ");
    // LOG_DEBUG(buttonStart.isHeldDown());

    // LOG_DEBUG("First button: ");
    // LOG_DEBUG(button1.isDown());

    // LOG_DEBUG("Second button: ");
    // LOG_DEBUG(button2.isDown());

    // LOG_DEBUG("Third button: ");
    // LOG_DEBUG(button3.isDown());

    // LOG_DEBUG("Hall state: ");
    // LOG_DEBUG(hallState);

    Display::onStartRotation(33333); //5 seconds
    timesToWait--;

    // delay(5000);

    delay(35);
}

void ISRButtonStart()
{
    buttonStart.onStateChange();
}

void ISRButton1()
{
    button1.onStateChange();
}

void ISRButton2()
{
    button2.onStateChange();
}

void ISRButton3()
{
    button3.onStateChange();
}

void ISRHall()
{
    hallState = !hallState;
    if (!hallState) // hallState is now 0, new rotation
    {
        lastRotationDuration = micros() - lastRotationStart;
        lastRotationStart = micros();

        // Display::onStartRotation(lastRotationDuration); // TODO: uncomment after fixing the wiring
    }
}
