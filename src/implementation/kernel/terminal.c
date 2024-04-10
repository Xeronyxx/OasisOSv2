#include "standard.h"
#include "print.h"

void terminal() {
    prints("> ");
    char input[64];
    char *cpy = cpyin(sizeof(input));
    strncpy(input, cpy, sizeof(input));
    prints("\n> ");
}