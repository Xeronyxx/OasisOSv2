#include <stddef.h>
#include "standard.h"
#include "keyboard.h"
#include "keymap.h"
#include "print.h"

unsigned long long time() {
    /* not working */

    volatile unsigned long long *timer_address = (volatile unsigned long long *)0x10000000;
    return *timer_address; /* idk what format this is in lmao */
}

char *cpyin(size_t buflim) {
    static char typedData[128] = "";
    int keyPressed = false;
    size_t typedDataLen = 0;

    while (1) {
        uint8_t key = scanKey();

        if (key == 0) {
            keyPressed = false;
        }

        if (!keyPressed) {
            keyPressed = true;

            if (key != KEY_ENTER && key != KEY_BACK) {
                if (typedDataLen < buflim - 1) {
                    char keyChar = uint8_convert(key);
                    typedData[typedDataLen] = keyChar;
                    typedDataLen++;
                    typedData[typedDataLen] = '\0';
                    print_char(keyChar);
                }
            }

            if (key == KEY_ENTER) { break; }

            if (key == KEY_BACK && typedDataLen > 0) {
                remove_chars(1);
                typedDataLen--;
                typedData[typedDataLen] = '\0';
            }
        }
    }

    return typedData;
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

size_t strlen(const char *str) {
    size_t length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

int strcmp(const char* str1, const char* str2){
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
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

void strncpy(char *dest, const char *src, size_t n){
    while (*src != '\0' && n > 0){
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    if (n > 0){
        *dest = '\0';
    }
}