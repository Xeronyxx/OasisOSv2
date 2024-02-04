#include "system.h"
#include "print.h"
#include "standard.h"

crashed = false;

void crash(int code) {
    crashed = true;
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
    print_str("SYSTEM HAS CRASHED. CODE: ");
    print_int(code);
    print_str(". \nPRESS ENTER TO EXIT.");

    /*while (1) {
        if (keyboard_enabled() == true) {
            if (keyboard_get_key() == "\n") {
                break;
            }
        } else {
            break;
        }
    }*/
}

unsigned short getMemorySize() {
    struct BDA *bda = (struct BDA *)((uint64_t)0x40 << 4 | 0xE);
    return bda->memorySize;
}