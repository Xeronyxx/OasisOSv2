#include "keyboard.h"
#include "process.h"
#include "standard.h"
#include "mem.h"
#include <stdint.h>

uint8_t scan_key() {
    uint8_t scan_code = inb(0x60);

    if (scan_code & 0x80) {
        return 0;
    }
    
    return scan_code;
}