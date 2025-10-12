#include <stdint.h>
#include <stdbool.h>
#include <../types/types.h>


#ifndef OPERATION_TYPE_T
#define OPERATION_TYPE_T


typedef enum op_type_t {
    IMMEDIATE, // Value to register        
    STRAIGHT, // Register to register         
    SET_INDEX, // Value to index register      
    DELAY_TIMER, // Delay timer to register      
    KEY_PRESSED, // Key pressed to register      
    SET_DELAY_TIMER, // Register to delay timer  
    SET_SOUND_TIMER, // Register to sound timer
    FONT, // Register to font             
    BCD, // Split register to decimals              
    REGISTER_TO_ARRAY, // Set n registers to n index registers
    ARRAY_TO_REGISTER, // Set n index registers to n registers
    BUTTON_PRESSED,
    BUTTON_NOT_PRESSED
} op_type_t;


#endif


#ifndef SYSCALLS_H
#define SYSCALLS_H


/*
0x1nnn - JMP nnn
PC = nnn, Jump to PC

0xBnnn - JMP V0, nnn
PC = nnn + v0, Jump to PC

Tip: PC = address[0] + address[1]
*/
void
JMP(cpu_t* cpu, uint16_t address[2], op_type_t type);



/* 
0x2nnn - CALL nnn
Call coroutine on 0xnnn address.
*/
void
CALL(cpu_t* cpu, uint16_t coroutine);


/*
0x3xkk - SE Vx, kk
Skip next instruction, if Vx == kk.

0x5xy0 - SE Vx, Vy
Skip next instruction, if Vx == Vy.

Tip: Skip if Equal
*/
void
SE(cpu_t* cpu, uint8_t Vx, uint8_t val2, op_type_t type);



/*
0x3xkk - SNE Vx, kk
Skip next instruction, if Vx != kk.

0x9xy0 - SNE Vx, Vy
Skip next instruction if Vx != Vy.

Tip: Skip if NOT Equal
*/
void
SNE(cpu_t* cpu, uint8_t val1, uint8_t val2, op_type_t type);



/*
0x6xkk - LOAD Vx, kk
0x8xy0 - LOAD Vx, Vy 
0xAnnn - LOAD I, nnn
0xFx07 - LOAD Vx, DT  
0xFx0A - LOAD Vx, Key
0xFx15 - LOAD DT, Vx 
0xFx18 - LOAD ST, Vx  
0xFx29 - LOAD Font, Vx 
0xFx33 - LOAD BCD, Vx   
0xFx55 - LOAD [I], Vx   
0xFx65 - LOAD Vx, [I]   

Tip: to = from
*/
void
LOAD(cpu_t* cpu, uint16_t to, uint16_t from, op_type_t type);


/*
0x7xkk - ADD Vx, kk
0x8xy4 - ADD Vx, Vy
0xFx1E - ADD I, Vx

Tip: val1 += val2
*/
void
ADD(cpu_t* cpu, uint8_t val1, uint8_t val2, op_type_t type);



/*
0x8xy5 - SUB Vx, Vy

Tip: val1 -= val2
*/
void
SUB(cpu_t* cpu, uint8_t val1, uint8_t val2);



/*
0x8xy7 - SUBN Vx, Vy

Tip: val1 = val2 - val1
*/
void
SUBN(cpu_t* cpu, uint8_t val1, uint8_t val2);



/*
0x8xy1 - OR Vx, Vy

Tip: val1 |= val2
*/
void
OR(cpu_t* cpu, uint8_t val1, uint8_t val2);



/*
0x8xy2 - AND Vx, Vy

Tip: val1 &= val2
*/
void
AND(cpu_t* cpu, uint8_t val1, uint8_t val2);



/*
0x8xy3 - XOR Vx, Vy

Tip: val1 ^= val2
*/
void
XOR(cpu_t* cpu, uint8_t val1, uint8_t val2);



/*
0x8xy6 - SHR Vx

Tip: vF = vx & 1, vx >>= 1
*/
void
SHR(cpu_t* cpu, uint8_t val1);



/*
0x8xyE - SHL Vx

Tip: vF = vx & 0x80, vx <<= 1
*/
void
SHL(cpu_t* cpu, uint8_t register);



/*
0xCxkk - RND Vx, kk

Tip: Vx = random() & kk
*/
void
RND(cpu_t* cpu, uint8_t Vx, uint8_t val);



/*
0xDxyn - DRW Vx, Vy, N
Draw sprite 8px wide and Npx height, on (Vx;Vy) coordinates.

Tip: here i forgot how DRW works
*/
void
DRW();



/*
0xEx9E - SKP Vx
Skip instruction if key with code in Vx IS PRESSED.

0xExA1 - SKP Vx
Skip instruction if key with code in Vx IS NOT PRESSED.
*/
bool
SKP(cpu_t* cpu, button_t button, op_type_t type);


#endif