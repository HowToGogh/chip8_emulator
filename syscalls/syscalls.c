#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "syscalls.h"
#include "../types/types.h"


void
JMP(cpu_t* cpu, uint16_t address[2], op_type_t type) {

    switch (type) {

        case STRAIGHT:
            cpu->PC = address[0];
            break;

        case IMMEDIATE:
            cpu->PC = address[0] + address[1];
            break;
        
        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }

}



void
CALL(cpu_t* cpu, uint16_t coroutine) {

    if (cpu->SP <= 15) {
        cpu->stack[cpu->SP] = cpu->PC;
        cpu->PC = coroutine;
        ++cpu->SP;
    }
    else {
        fprintf(stderr, "Stack overflow.\n");
        exit(-1);
    }

}



void
SE(cpu_t* cpu, uint8_t Vx, uint8_t val2, op_type_t type) {

    switch (type) {

        case IMMEDIATE:
            if (Vx < 16) {
                cpu->registers[Vx] == val2 ? cpu->PC += 2 : 0 ;
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;

        case STRAIGHT:
            if (Vx < 16 && val2 < 16) {
                cpu->registers[Vx] == cpu->registers[val2] ? cpu->PC += 2 : 0 ;
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;
        
        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }

}



void
SNE(cpu_t* cpu, uint8_t Vx, uint8_t val2, op_type_t type) {

    switch (type) {

        case IMMEDIATE:
            if (Vx < 16) {
                cpu->registers[Vx] != val2 ? cpu->PC += 2 : 0 ;
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;

        case STRAIGHT:
            if (Vx < 16 && val2 < 16) {
                cpu->registers[Vx] != cpu->registers[val2] ? cpu->PC += 2 : 0 ;
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;
        
        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }

}



void
LOAD(cpu_t* cpu, uint16_t to, uint16_t from, op_type_t type) {
    switch (type) {

        case IMMEDIATE:
            cpu->registers[(uint8_t)to] = (uint8_t)from;
            break;  

        case STRAIGHT:
            cpu->registers[(uint8_t)to] = cpu->registers[(uint8_t)from];
            break;  

        case SET_INDEX:
            cpu->I = from & 0xFFF;
            break;

        case DELAY_TIMER:
            cpu->registers[(uint8_t)to] = cpu->DT;
            break;

        case KEY_PRESSED:
            // damn hard ahhhh
            break;

        case SET_DELAY_TIMER:
            cpu->DT = (uint8_t)cpu->registers[from];
            break; 

        case SET_SOUND_TIMER:
            cpu->ST = (uint8_t)cpu->registers[from];
            break; 

        case FONT:
            // damn hard ahhhh
            break; 

        case BCD:
            cpu->memory[cpu->I + 0] = (uint8_t)cpu->registers[from] / 100;
            cpu->memory[cpu->I + 1] = (uint8_t)cpu->registers[from] / 10 % 10;
            cpu->memory[cpu->I + 2] = (uint8_t)cpu->registers[from] % 10;
            break; 

        case REGISTER_TO_ARRAY:
            for (uint8_t x = 0; x < (uint8_t)to; ++x) {
                cpu->memory[cpu->I + x] = cpu->registers[x];
            }
            break; 

        case ARRAY_TO_REGISTER:
            for (uint8_t x = 0; x < (uint8_t)to; ++x) {
                cpu->registers[x] = cpu->memory[cpu->I + x];
            }
            break;
        
        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }
}



void
ADD(cpu_t* cpu, uint8_t val1, uint8_t val2, op_type_t type) {

    switch (type) {

        case IMMEDIATE:
            if (val1 < 16) {
                cpu->registers[val1] += val2;
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;

        case STRAIGHT:
            if (val1 < 16 && val2 < 16) {
                cpu->registers[val1] += cpu->registers[val2];
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;

        case SET_INDEX:
            if (val1 < 16) {
                cpu->I += cpu->registers[val1];
            }
            else {
                fprintf(stderr, "Invalid value.\n");
                exit(-1);
            }
            break;

        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }

}



void
SUB(cpu_t* cpu, uint8_t Vx, uint8_t Vy) {

    if (Vx < 16 && Vy < 16) {
        cpu->registers[Vx] -= cpu->registers[Vy];
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }
}



void
SUBN(cpu_t* cpu, uint8_t Vx, uint8_t Vy) {

    if (Vx < 16 && Vy < 16) {
        cpu->registers[Vx] = cpu->registers[Vy] - cpu->registers[Vx];
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);

    }
}



void
OR(cpu_t* cpu, uint8_t Vx, uint8_t Vy) {

    if (Vx < 16 && Vy < 16) {
        cpu->registers[Vx] |= cpu->registers[Vy];
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }

}



void
AND(cpu_t* cpu, uint8_t Vx, uint8_t Vy) {

    if (Vx < 16 && Vy < 16) {
        cpu->registers[Vx] &= cpu->registers[Vy];
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }

}



void
XOR(cpu_t* cpu, uint8_t Vx, uint8_t Vy) {

    if (Vx < 16 && Vy < 16) {
        cpu->registers[Vx] ^= cpu->registers[Vy];
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }

}



void
SHR(cpu_t* cpu, uint8_t Vx) {

    if (Vx < 16) {
        cpu->registers[15] = cpu->registers[Vx] & 0x1;
        cpu->registers[Vx] >>= 1;
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }

}



void
SHL(cpu_t* cpu, uint8_t Vx) {

    if (Vx < 16) {
        cpu->registers[15] = (cpu->registers[Vx] & 0x80) >> 7;
        cpu->registers[Vx] <<= 1;
    }
    else {
        fprintf(stderr, "Invalid value.\n");
        exit(-1);
    }

}



void
RND(cpu_t* cpu, uint8_t Vx, uint8_t val) {

    // pseudo-random numbers
    static uint8_t numbers[128] = {
        42,  198, 124, 0,   255, 17,  233, 89,
        200, 66,  70,  88,  152, 221, 31,  145,
        99,  177, 234, 12,  111, 78,  245, 167,
        59,  23,  29,  91,  210, 142, 47,  5,
        75,  138, 180, 36,  219, 102, 189, 115,
        28,  162, 250, 200, 83,  155, 63,  229,
        131, 44,  16,  173, 96,  241, 19,  137,
        72,  150, 254, 107, 33,  184, 121, 205
    };
    static int count = 0;

    if (count < 255) {
        cpu->registers[Vx] = numbers[count] & val;
        ++count;
    }
    else if (count == 255) {
        cpu->registers[Vx] = numbers[count] & val;
        count = 0;
    }

}



void
DRW() {};



bool
SKP(cpu_t* cpu, button_t button, op_type_t type) {
    switch (type) {

        case BUTTON_PRESSED:
            if (button.pressed) {
                cpu->PC += 2;
            }
            break;
        
        case BUTTON_NOT_PRESSED:
            if (!button.pressed) {
                cpu->PC += 2;
            }
            break;

        default:
            fprintf(stderr, "Wrong operation type.\n");
            exit(-1);

    }
}