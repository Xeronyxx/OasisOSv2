#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_POOL_SIZE 1024

void *memcpy(void *dest, const void *src, uint8_t n);

#endif // MEM_H