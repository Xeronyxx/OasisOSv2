#include "random.h"
#include "system.h"

int rand() {
    return (RAND_A * get_memory_size() + RAND_C) % RAND_MAX;
}