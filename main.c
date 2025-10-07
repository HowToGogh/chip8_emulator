#include <stdio.h>
#include <string.h>

#include "types/types.h"
#include "init/init.h"

int main() {

    display_t Display;
    cpu_t CPU;
    keyboard_t Keyboard;
    
    display_init(&Display);
    cpu_init(&CPU);
    keyboard_init(&Keyboard);

    return 0;
    
}