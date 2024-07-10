#ifndef SYS_H
#define SYS_H

extern int crashed;

struct BDA {
    unsigned short memorySize;
};

unsigned short get_memory_size();
void crash(int code, char *reason);
void reboot();
void sysexit();
void sleep(unsigned int ms);

#endif // SYS_H