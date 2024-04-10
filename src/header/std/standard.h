#include <stddef.h>
#pragma once

#define false 0
#define true 1

unsigned long long time();
void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);