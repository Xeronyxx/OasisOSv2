#pragma once

extern int crashed;

struct BDA {
    unsigned short memorySize;
};

unsigned short getMemorySize();
void crash(int code, char *reason);
void reboot();
void sleep(unsigned int ms);