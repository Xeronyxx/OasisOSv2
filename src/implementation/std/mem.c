#include "mem.h"

void *memcpy(void *dest, const void *src, uint8_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;

    for (uint8_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }

    return dest;
}