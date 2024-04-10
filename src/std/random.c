#include "random.h"
#include "system.h"

int rand() {
    return (RAND_A * getMemorySize() + RAND_C) % RAND_MAX;
}