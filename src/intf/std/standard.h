#include <stddef.h>
#pragma once

#define false 0
#define true 1

char *cpyin(size_t buflim);
void strcpy(char *dest, const char *src, size_t size);
size_t strlen(const char *str);
char *strncat(char *dest, const char *src, size_t n);
void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
char *strcat(char *dest, const char *src);