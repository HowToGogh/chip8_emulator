#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef PARAMETERS
#define PARAMETERS

#define DISPLAY_HEIGHT  32      //
#define DISPLAY_WIDTH   64      //
#define STACK_SIZE      16      //
#define RAM_SIZE        4096    //

#endif

#ifndef TYPES_H
#define TYPES_H

extern uint8_t fonts[80];

typedef struct display_t {
    char monitor[DISPLAY_HEIGHT][DISPLAY_WIDTH];
} display_t;

typedef struct button_t {
    char key;
    bool pressed;
} button_t;

typedef struct keyboard_t {
    button_t keys[16];
} keyboard_t;

typedef struct cpu_t {        
    uint16_t PC;                // Program Counter - points to the NEXT program
    uint16_t I;                 // Index register - points to address in memory (like data AICS)
    uint16_t stack[STACK_SIZE]; // Stack - i know how it works, but my english is not enough to explain ;(
    uint16_t SP;                // Stack Pointer - points to the TOP of stack
    uint8_t DT;                 // Delay Timer
    uint8_t ST;                 // Sound Timer
    uint8_t registers[16];      // 16 registers, from V0 to VF - general-purpose registers
    uint8_t memory[RAM_SIZE];   // RAM, writable
} cpu_t;

#endif 