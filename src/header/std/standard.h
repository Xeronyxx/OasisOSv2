#ifndef STD_H
#define STD_H

#include <stddef.h>

#define false 0
#define true 1

unsigned long long time();
void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
void arrclear(char *array, int size);

#endif // STD_H