#include "system.h"
#include "print.h"
#include "standard.h"
#include "keyboard.h"
#include "random.h"

int crashed = false;

void crash(int code, char *reason) {
    crashed = true;

    char *emoticons[16] = {
        "D:",
        ":(",
        ":)",
        ":/",
        ":\\",
        ":C",
        ":c",
        "x_x",
        ":[",
        "]:",
        ":|",
        "|:",
        "o_o",
        ":o",
        "o:",
        ":P"
    };
    char *selectedEmoticon = emoticons[rand() % 16];

    cls();
    screen_colour(PRINT_COLOUR_WHITE | PRINT_COLOUR_BLUE << 4);
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLUE);
    prints("\n\n\n\n                    ");
    prints(selectedEmoticon);
    prints("\n\n");
    prints("                    OPERATING SYSTEM HAS CRASHED!\n\n\n\n                    CODE: ");
    printi(code);
    prints("\n                    REASON: ");
    prints(reason);
    prints("\n\n\n\n                    PRESS ANY KEY TO REBOOT.\n");

    while (1) {
        if (scan_key() != 0)
            reboot();
            break; // Just in case
    }
}

unsigned short get_memory_size() {
    struct BDA *bda = (struct BDA *)0x400;
    return bda->memorySize;
}

void reboot(){
    asm volatile (
        "int $0x19"
    );
}

void sysexit() {
    asm volatile (
        "mov $0x5307, %ax\n"
        "mov $0x1, %bx\n"
        "mov $0x3, %cx\n"
        "int $0x15"
    );
}

void sleep(unsigned int ms){
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