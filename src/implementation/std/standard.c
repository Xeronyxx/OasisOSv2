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