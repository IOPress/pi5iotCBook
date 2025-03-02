// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --- //
// dht //
// --- //

#define dht_wrap_target 0
#define dht_wrap 22
#define dht_pio_version 0

static const uint16_t dht_program_instructions[] = {
            //     .wrap_target
    0xe001, //  0: set    pins, 1                    
    0xe081, //  1: set    pindirs, 1                 
    0x80a0, //  2: pull   block                      
    0xe000, //  3: set    pins, 0                    
    0xa027, //  4: mov    x, osr                     
    0x0045, //  5: jmp    x--, 5                     
    0xe080, //  6: set    pindirs, 0                 
    0x20a0, //  7: wait   1 pin, 0                   
    0x2020, //  8: wait   0 pin, 0                   
    0x20a0, //  9: wait   1 pin, 0                   
    0x2020, // 10: wait   0 pin, 0                   
    0xe05f, // 11: set    y, 31                      
    0x39a0, // 12: wait   1 pin, 0               [25]
    0x4001, // 13: in     pins, 1                    
    0x2020, // 14: wait   0 pin, 0                   
    0x008c, // 15: jmp    y--, 12                    
    0xe047, // 16: set    y, 7                       
    0x39a0, // 17: wait   1 pin, 0               [25]
    0x4001, // 18: in     pins, 1                    
    0x2020, // 19: wait   0 pin, 0                   
    0x0091, // 20: jmp    y--, 17                    
    0x8020, // 21: push   block                      
    0x0002, // 22: jmp    2                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program dht_program = {
    .instructions = dht_program_instructions,
    .length = 23,
    .origin = -1,
    .pio_version = dht_pio_version,
#if PICO_PIO_VERSION > 0
    .used_gpio_ranges = 0x0
#endif
};

static inline pio_sm_config dht_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + dht_wrap_target, offset + dht_wrap);
    return c;
}
#endif

