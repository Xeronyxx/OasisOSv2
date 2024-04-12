/**
 * Program: Oasis Compiler
 * 
 * A compiler made for the default
 * programming language that users can
 * program in to make programs.
*/

#include "oasiscomp.h"
#include "str.h"
#include "filesystem.h"
#include "print.h"

void oscomp(char code[256], char *filename) {
    char *watermark = "--OASIS COMPILER--\n";

    char result[256];
    char *token;

    token = strtok(code, "\n");

    strcat(result, watermark);

    while(token != NULL) {
        if (strcmp(token, "PRINT") == 0) {
            result[strlen(result)] = 0x1;

            token = strtok(NULL, "\n");

            strcat(result, "\n");
            strcat(result, token);
        } else {
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
    prints("`");

    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    strcat(result, "\n");
    strcat(result, watermark);

    fs_write(result, fname);
}