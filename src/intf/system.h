#pragma once

extern int crashed;
void crash(int code);

struct BDA {
    unsigned short memorySize;
};

unsigned short getMemorySize();
void reboot();
void sleep(unsigned int ms);