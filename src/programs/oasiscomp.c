/**
 * Program: Oasis Compiler
 * 
 * A compiler made for the default
 * programming language that users can
 * program in it to make programs.
*/

#include "oasiscomp.h"
#include "str.h"
#include "filesystem.h"
#include "print.h"
#include "standard.h"

char *watermark = "--OASIS COMPILER--\n";

void oscomp(char code[256], char *filename) {
    char result[256];
    char *token;

    token = strtok(code, "\n");
    strcat(result, watermark);

    while (token != NULL) {
        int empty = true;
        for (int i = 0; i != '\0'; i++) {
            if (token[i] != ' ') {
                empty = false;
                break;
            }
        }

        if (strcmp(token, "PRINT") == 0) {
            result[strlen(result)] = 0x1;

            token = strtok(NULL, "\n");

            strcat(result, "\n");
            strcat(result, token);
        } else if (!empty) {
            print_set_colour(PRINT_COLOUR_RED, PRINT_COLOUR_BLACK);

            prints("Invalid instruction: `");
            prints(token);
            prints("`\n");

            print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
        }

        token = strtok(NULL, "\n");
    }

    char fname[128];
    
    for (int i = 0; filename[i] != '.'; i++) {
        fname[i] = filename[i];
    }
    strcat(fname, ".0");

    print_set_colour(PRINT_COLOUR_GREEN, PRINT_COLOUR_BLACK);

    prints("Compiled file as `");
    prints(fname);
    prints("`\n");

    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    strcat(result, "\n");
    strcat(result, watermark);

    fs_write(result, fname);
}