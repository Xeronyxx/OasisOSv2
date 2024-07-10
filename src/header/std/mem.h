#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_POOL_SIZE 1024

typedef struct Block {
    size_t size;
    struct Block *next;
    int free;
} Block;

#define BLOCK_SIZE (sizeof(Block))

void *memcpy(void *dest, const void *src, uint8_t n);
void mem_init();
void *malloc(size_t size);
void free(void *ptr);

#endif // MEM_H