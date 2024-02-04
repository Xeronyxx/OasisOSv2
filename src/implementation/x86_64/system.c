#include "system.h"
#include "print.h"
#include "standard.h"
#include "keyboard.h"

crashed = false;

void crash(int code) {
    crashed = true;
    print_clear();
    print_set_colour(PRINT_COLOUR_RED, PRINT_COLOUR_WHITE);
    print_str("KERNEL PANIC!\nCODE: ");
    print_int(code);
    print_str(". \nPRESS ENTER TO EXIT.");
    waitForKeyPress(KEY_ENTER);
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
    print_str("The system will now reboot...");
    reboot();

    while (1) {
        if (scanKey() == KEY_ENTER) {
            break;
        }
    }
}

unsigned short getMemorySize() {
    struct BDA *bda = (struct BDA *)0x400;
    return bda->memorySize;
}

void reboot(){
    asm volatile (
        "int $0x19"
    );
}