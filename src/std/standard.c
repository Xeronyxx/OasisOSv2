#include <stddef.h>
#include "standard.h"
#include "keyboard.h"
#include "keymap.h"
#include "print.h"

unsigned long long time() {
    /* not working */

    volatile unsigned long long *timer_address = (volatile unsigned long long *)0x10000000;
    return *timer_address;
}

void arrclear(char *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = '\0';
    }
}

void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}