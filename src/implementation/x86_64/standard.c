#include <stddef.h>
#include "standard.h"

size_t strlen(const char *str) {
    size_t length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}