#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <stdint.h>

#define DEBUG 1

// use ## because otherwise you need to put an extra comma in order to not get an error when using it with no extra arguments (LOG_DEBUG("test",);)
#define LOG_INFO(x, ...) LOG(x, "INFO: ", ##__VA_ARGS__)
#define LOG_DEBUG(x, ...) LOG(x, "DEBUG: ", ##__VA_ARGS__)
#define LOG_ERROR(x, ...) LOG(x, "ERROR: ", ##__VA_ARGS__)

#if DEBUG
#define LOG(x, tag, ...)                 \
    {                                     \
        char charbuffer[100];           \
        sprintf(charbuffer, x, ##__VA_ARGS__);\
        Serial.print(tag);          \
        Serial.println(charbuffer);           \
    }
#else
#define LOG(x, tag, ...)
#endif

#define SIZE(x) sizeof(x)/sizeof(x[0])

#define BUTTON_START A0
#define BUTTON_1 A3
#define BUTTON_2 A2
#define BUTTON_3 A1
#define HALL_SENSOR A4

#endif