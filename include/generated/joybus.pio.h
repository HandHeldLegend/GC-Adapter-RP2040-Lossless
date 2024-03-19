// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------ //
// joybus //
// ------ //

#define joybus_wrap_target 0
#define joybus_wrap 25

#define joybus_offset_joybusdelay 0u
#define joybus_offset_joybusout 6u

static const uint16_t joybus_program_instructions[] = {
            //     .wrap_target
    0xa742, //  0: nop                           [7] 
    0xa742, //  1: nop                           [7] 
    0xa742, //  2: nop                           [7] 
    0xa742, //  3: nop                           [7] 
    0xa642, //  4: nop                           [6] 
    0x0080, //  5: jmp    y--, 0                     
    0xe080, //  6: set    pindirs, 0                 
    0x6321, //  7: out    x, 1                   [3] 
    0xf081, //  8: set    pindirs, 1      side 0     
    0x132e, //  9: jmp    !x, 14          side 0 [3] 
    0xe080, // 10: set    pindirs, 0                 
    0xa242, // 11: nop                           [2] 
    0x1de6, // 12: jmp    !osre, 6        side 1 [5] 
    0x0010, // 13: jmp    16                         
    0xb142, // 14: nop                    side 0 [1] 
    0x17e6, // 15: jmp    !osre, 6        side 0 [7] 
    0xe080, // 16: set    pindirs, 0                 
    0xa342, // 17: nop                           [3] 
    0xf081, // 18: set    pindirs, 1      side 0     
    0xb142, // 19: nop                    side 0 [1] 
    0xf880, // 20: set    pindirs, 0      side 1     
    0xa0c3, // 21: mov    isr, null                  
    0x2720, // 22: wait   0 pin, 0               [7] 
    0x4001, // 23: in     pins, 1                    
    0x20a0, // 24: wait   1 pin, 0                   
    0x0016, // 25: jmp    22                         
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program joybus_program = {
    .instructions = joybus_program_instructions,
    .length = 26,
    .origin = -1,
};

static inline pio_sm_config joybus_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + joybus_wrap_target, offset + joybus_wrap);
    sm_config_set_sideset(&c, 2, true, false);
    return c;
}

// Joybus program hogs all four state machines simultaneously 
static inline void joybus_program_init(PIO pio, uint offset, uint pin, pio_sm_config *configs) {
    // Must run 12800000hz
    float div = clock_get_hz(clk_sys) / (4000000);
    for(uint i = 0; i < 4; i++)
    {
        configs[i] = joybus_program_get_default_config(offset);
        gpio_init(pin+i);
        // Set this pin's GPIO function (connect PIO to the pad)
        pio_gpio_init(pio, pin+i);
        pio_sm_set_consecutive_pindirs(pio, i, pin+i, 1, true);
        sm_config_set_in_pins(&configs[i], pin+i);
        sm_config_set_out_pins(&configs[i], pin+i, 1);
        sm_config_set_jmp_pin(&configs[i], pin+i);
        sm_config_set_set_pins(&configs[i], pin+i, 1);
        sm_config_set_clkdiv(&configs[i], div);
        // Set sideset pin
        sm_config_set_sideset_pins(&configs[i], pin+i);
        sm_config_set_in_shift(&configs[i], false, true, 32);
        sm_config_set_out_shift(&configs[i], false, true, 8);
        // Load our configuration, and jump to the start of the program
        pio_sm_init(pio, i, offset, &configs[i]);
        // Set the state machine running
        pio_sm_set_enabled(pio, i, true);
    } 
}

#endif

