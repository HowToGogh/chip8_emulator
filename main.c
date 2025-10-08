#include <stdio.h>
#include <string.h>

#include "types/types.h"
#include "init/init.h"

display_t Display;
cpu_t CPU;
keyboard_t Keyboard;

int main() {
    
    display_init(&Display);
    cpu_init(&CPU);
    keyboard_init(&Keyboard);

    return 0;
    
}