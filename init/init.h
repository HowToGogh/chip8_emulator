#pragma once

#ifndef INIT_H
#define INIT_H

#include "../types/types.h"

void
cpu_init(cpu_t* cpu);

void 
display_init(display_t* display);

void
keyboard_init(keyboard_t* keyboard);

#endif