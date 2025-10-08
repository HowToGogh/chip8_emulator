#include <stdint.h>
#include <stdbool.h>
#include <../types/types.h>


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
JMP(uint16_t address[2]);



/* 
0x2nnn - CALL nnn
Call coroutine on 0xnnn address.
*/
void
CALL(uint16_t coroutine);



/*
0x3xkk - SE Vx, kk
Skip next instruction, if Vx == kk.

0x5xy0 - SE Vx, Vy
Skip next instruction, if Vx == Vy.

Tip: Skip if Equal
*/
bool
SE(uint8_t val1, uint8_t val2);



/*
0x3xkk - SNE Vx, kk
Skip next instruction, if Vx != kk.

0x9xy0 - SNE Vx, Vy
Skip next instruction if Vx != Vy.

Tip: Skip if NOT Equal
*/
bool
SNE(uint8_t val1, uint8_t val2);



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
LOAD(uint8_t to, uint8_t from);



/*
0x7xkk - ADD Vx, kk
0x8xy4 - ADD Vx, Vy
0xFx1E - ADD I, Vx

Tip: val1 += val2
*/
void
ADD(uint8_t val1, uint8_t val2);



/*
0x8xy5 - SUB Vx, Vy

Tip: val1 -= val2
*/
void
SUB(uint8_t val1, uint8_t val2);



/*
0x8xy7 - SUBN Vx, Vy

Tip: val1 = val2 - val1
*/
void
SUBN(uint8_t val1, uint8_t val2);



/*
0x8xy1 - OR Vx, Vy

Tip: val1 |= val2
*/
void
OR(uint8_t val1, uint8_t val2);



/*
0x8xy2 - OR Vx, Vy

Tip: val1 &= val2
*/
void
AND(uint8_t val1, uint8_t val2);



/*
0x8xy3 - XOR Vx, Vy

Tip: val1 ^= val2
*/
void
XOR(uint8_t val1, uint8_t val2);



/*
0x8xy6 - SHR Vx

Tip: vF = vx & 1, vx >>= 1
*/
void
SHR(uint8_t register);



/*
0x8xyE - SHL Vx

Tip: vF = vx & 0x80, vx <<= 1
*/
void
SHL(uint8_t register);



/*
0xCxkk - RND Vx, kk

Tip: register = random() & kk
*/
void
RND(uint8_t register, uint8_t val);



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
SKP(button_t button);

#endif