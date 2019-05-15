#define DEBUG 1

// use ## because otherwise you need to put an extra comma in order to not get an error when using it with no extra arguments (LOG_DEBUG("test",);)
#if DEBUG
#define LOG_DEBUG(x, ...)                 \
    {                                     \
        char charbuffer[100];           \
        sprintf(charbuffer, x, ##__VA_ARGS__);\
        Serial.print("DEBUG: ");          \
        Serial.println(charbuffer);           \
    }
#else
#define LOG_DEBUG(x)
#endif

#define BUTTON_START A0
#define BUTTON_1 A1
#define BUTTON_2 A2
#define BUTTON_3 A3
#define HALL_SENSOR A4