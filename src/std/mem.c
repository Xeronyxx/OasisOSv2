#include "mem.h"
#include <stddef.h>

// What a fucking pain the ass it was
// it to implement malloc and free

void *memcpy(void *dest, const void *src, uint8_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;

    for (uint8_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }

    return dest;
}

static char memory_pool[MEMORY_POOL_SIZE];
static char *free_list = memory_pool;

void mem_init() {
    Block *initial_block = (Block *)memory_pool;
    initial_block->size = MEMORY_POOL_SIZE - BLOCK_SIZE;
    initial_block->next = NULL;
    initial_block->free = 1;
}

void *malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    Block *current = (Block *)free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size >= size + BLOCK_SIZE + 1) {
                Block *block = (Block *)((char *)current + BLOCK_SIZE + size);
                block->size = current->size - size - BLOCK_SIZE;
                block->next = current->next;
                block->free = 1;
                current->next = block;
                current->size = size;
            }
            current->free = 0;
            return (char *)current + BLOCK_SIZE;
        }
        current = current->next;
    }
    return NULL;
}

void free(void *ptr) {
    if (ptr == NULL)
        return;

    Block *block = (Block *)((char *)ptr - BLOCK_SIZE);
    block->free = 1;

    Block *current = (Block *)free_list;
    while (current != NULL) {
        if (current->free) {
            Block *next = current->next;
            while (next != NULL && next->free) {
                current->size += BLOCK_SIZE + next->size;
                current->next = next->next;
                next = next->next;
            }
        }
        current = current->next;
    }
}