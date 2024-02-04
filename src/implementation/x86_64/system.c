#include "system.h"
#include "print.h"
#include "standard.h"
#include "keyboard.h"

crashed = false;

void crash(int code) {
    crashed = true;
    print_clear();
    print_set_colour(PRINT_COLOUR_RED, PRINT_COLOUR_BLACK);
    print_str("KERNEL PANIC!\nCODE: ");
    print_int(code);
    print_str(". \nPRESS ENTER TO EXIT.\n");
    waitForKeyPress(KEY_ENTER);
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
    print_str("The system will now reboot...\n");
    wait(1000);
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

void wait(unsigned int ms){
    unsigned int loops = ms * 10000;

    asm volatile (
        "mov %0, %%ecx;"
        "1:;"
        "pause;"
        "loop 1b;"
        :
        : "r"(loops)
        : "%ecx"
    );
}