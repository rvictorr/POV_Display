#include <interrupt.h>

#include "button.h"
#include "display.h"

#define DEBUG 1

// use ## because otherwise you need to put an extra comma in order to not get an error when using it with no extra arguments (LOG_DEBUG("test",);)
#if DEBUG
#define LOG_DEBUG(x, ...) {\
    Serial.print("DEBUG: ");\
    Serial.println(x, ##__VA_ARGS__);\
}
#else
#define LOG_DEBUG(x)
#endif

#define BUTTON_START A0
#define BUTTON_1 A1
#define BUTTON_2 A2
#define BUTTON_3 A3
#define HALL_SENSOR A4

Button buttonStart(BUTTON_START);
Button button1(BUTTON_1);
Button button2(BUTTON_2);
Button button3(BUTTON_3);

volatile int8_t hallState = 0;

void setup()
{
  Serial.begin(9600);

  Display::initPins();
    
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

  //updateLeds(0b0101010110);
}

void loop()
{
  
    
    LOG_DEBUG("-------START SERIAL-------\n");
    LOG_DEBUG("Start button: ");
    LOG_DEBUG(buttonStart.isHeld());

    LOG_DEBUG("First button: ");
    LOG_DEBUG(button1.isDown());
  
    LOG_DEBUG("Second button: ");
    LOG_DEBUG(button2.isDown());
  
    LOG_DEBUG("Third button: ");
    LOG_DEBUG(button3.isDown());

    LOG_DEBUG("Hall state: ");
    LOG_DEBUG(hallState);
    

    delay(10);
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
    if (hallState) // a new rotation starts
    {
        // do stuff
    }
}
