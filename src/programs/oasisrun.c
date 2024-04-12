/**
 * Program: Oasis Run
 * 
 * Runs a compiled OasisLang
 * object file. Default program
 * type for OasisOS.
*/

#include "oasisrun.h"
#include "str.h"
#include "print.h"

void osrun(char data[256]) {
    char *token;

    token = strtok(data, "\n");

    while (token != NULL) {
        if (*token == 0x1) {
            // PRINT
            token = strtok(NULL, "\n");
            prints(token);
        }

        token = strtok(NULL, "\n");
    }

    prints("\n");
}