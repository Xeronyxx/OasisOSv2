#include "standard.h"
#include "print.h"

void terminal() {
    while (1) {
        prints("> ");
        char input[64];
        char *cpy = cpyin(sizeof(input));
        strcpy(input, cpy, 64);
        prints("\n> ");
    }
}