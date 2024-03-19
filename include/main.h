#include "adapter_includes.h"
#include "ws2812.pio.h"
#include "joybus.pio.h"

#define RGB_PIO pio1
#define RGB_SM 0

#define RGB_RED_PIN 10
#define RGB_GREEN_PIN 9
#define RGB_BLUE_PIN 8

#define PWM_FREQ 10000 // PWM frequency in Hz
#define PWM_RANGE 255  // PWM range (0-255)

// Define PWM channels
#define PWM_CHANNEL_1 4
#define PWM_CHANNEL_2 5

#define JOYBUS_PIO pio0

#define JOYBUS_PORT_1 12
#define JOYBUS_PORT_2 13
#define JOYBUS_PORT_3 14
#define JOYBUS_PORT_4 15
