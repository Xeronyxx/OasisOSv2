#include "str.h"
#include "mem.h"
#include "standard.h"

char *strtok(char *str, const char *delim) {
    static char *ptr = NULL;
    static int inside = false;
    char *token_start = NULL;

    if (str != NULL)
        ptr = str;

    if (!inside) {
        while (*ptr != '\0' && strchr(delim, *ptr) != NULL)
            ptr++;
        inside = true;
    }

    if (*ptr == '\0')
        return NULL;

    token_start = ptr;

    while (*ptr != '\0' && strchr(delim, *ptr) == NULL)
        ptr++;

    if (*ptr != '\0') {
        *ptr = '\0';
        ptr++;
    } else {
        inside = false;
    }

    return token_start;
}

char *strchr(const char *s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0') {
        return (char *)s;
    }
    return NULL;
}

char *strcat(char *dest, const char *src) {
    char *temp = dest;

    while (*dest != '\0') {
        dest++;
    }

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
    return temp;
}

char *strsub(const char* str, int len) {
    static char dat[100];
    int ptr = 0;

    for (int i = len; str[i] != '\0'; i++) {
        dat[ptr] = str[i];
        ptr++;
    }
    dat[ptr] = '\0';

    return dat;
}

size_t strlen(const char *str) {
    size_t length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

int strcmp(char *str, char *comp) {
    int mismatches = 0;

    for (int i = 0; str[i] != '\0' || comp[i] != '\0'; i++) {
        if (str[i] != comp[i])
            mismatches++;
    }

    return mismatches;
}

int strncmp(char *str, char *comp, uint8_t n) {
    int mismatches = 0;

    for (int i = 0; (str[i] != '\0' || comp[i] != '\0') && i < n; i++) {
        if (str[i] != comp[i])
            mismatches++;
    }

    return mismatches;
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