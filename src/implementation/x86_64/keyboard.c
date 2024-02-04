#include <stdint.h>
#include "keyboard.h"

void bindKey(uint8_t key, void (*callback)()) {
    uint8_t scan_code;
    do {
        scan_code = scanKey();
    } while (scan_code != key);

    callback();
}

uint8_t scanKey() {
    uint8_t scan_code;
    asm volatile("inb %1, %0" : "=a"(scan_code) : "dN"(0x60));
    
    if (scan_code & 0x80) {
        return 0;
    }
    
    return scan_code;
}

void waitForKeyPress(uint8_t key){
    uint8_t scan_code;
    do {
        scan_code = scanKey();
    } while (scan_code != key);
}