#include "print.h"

int crashed = 0;

void crash(int code) {
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