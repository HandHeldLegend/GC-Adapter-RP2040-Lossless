#include "main.h"

uint slice_num_1, slice_num_2, slice_num_3;

void init_pwm() 
{
    // Initialize PWM
    gpio_set_function(RGB_RED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_GREEN_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_BLUE_PIN, GPIO_FUNC_PWM);

    // Get PWM slice numbers
    slice_num_1 = pwm_gpio_to_slice_num(RGB_RED_PIN);
    slice_num_2 = pwm_gpio_to_slice_num(RGB_GREEN_PIN);
    slice_num_3 = pwm_gpio_to_slice_num(RGB_BLUE_PIN);

    // Set PWM frequency and range
    pwm_set_wrap(slice_num_1, PWM_RANGE);
    pwm_set_wrap(slice_num_2, PWM_RANGE);
    pwm_set_wrap(slice_num_3, PWM_RANGE);
    pwm_set_clkdiv(slice_num_1, 125); // 125MHz / 125 = 1MHz
    pwm_set_clkdiv(slice_num_2, 125);
    pwm_set_clkdiv(slice_num_3, 125);

    // Enable PWM output
    pwm_set_enabled(slice_num_1, true);
    pwm_set_enabled(slice_num_2, true);
    pwm_set_enabled(slice_num_3, true);
}

// Set brightness for a specific LED
void set_led_brightness(uint pin, uint brightness) {
    pwm_set_gpio_level(pin, brightness);
}
void rgb_itf_update(rgb_s *leds)
{
    set_led_brightness(RGB_RED_PIN, 255-leds->r);
    set_led_brightness(RGB_GREEN_PIN, 255-leds->g);
    set_led_brightness(RGB_BLUE_PIN, 255-leds->b);
}

void rgb_itf_init()
{
    init_pwm();
}