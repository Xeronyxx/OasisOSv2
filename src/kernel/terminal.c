#include "keyboard.h"
#include "terminal.h"
#include "standard.h"
#include "str.h"
#include "print.h"
#include "keymap.h"
#include "filesystem.h"

void _CLS();
void _HELP();
void _LS();

void _ECHO(char *data);
void _MAKE(char *data);
void _PEAK(char *data);

void terminal() {
    char typedData[256] = "";
    int keyPressed = false;
    int lastKey = 0x0;

    prints("\n> ");

    while (1) {
        uint8_t key = scanKey();

        if (key == 0 || key != lastKey) {
            keyPressed = false;
        }

        if (keyPressed == false) {
            keyPressed = true;
            lastKey = key;

            if (key == KEY_ENTER) {
                prints("\n");

                char *arg;

                if (strcmp(typedData, "CLS") == 0) {
                    _CLS();
                } else if (strcmp(typedData, "HELP") == 0) {
                    _HELP();
                } else if (strncmp(typedData, "ECHO", 4) == 0) {
                    arg = strsub(typedData, 5);
                    _ECHO(arg);
                } else if (strcmp(typedData, "LS") == 0) {
                    _LS();
                } else if (strncmp(typedData, "MAKE", 4) == 0) {
                    arg = strsub(typedData, 5);
                    _MAKE(arg);
                } else if (strncmp(typedData, "PEAK", 4) == 0) {
                    arg = strsub(typedData, 5);
                    _PEAK(arg); 
                } else {
                    prints("Invalid command, type `HELP` for command info.\n");
                }

                typedData[0] = '\0';
                prints("> ");
            }

            if (key != 0 && key != KEY_ENTER && key != KEY_BACK) {
                print_char(uint8_convert(key));
                strncat(typedData, (char[]){uint8_convert(scanKey()), '\0'}, 1);
            }
            
            if (key == KEY_BACK) {
                if (strlen(typedData) > 0) {
                    int len = strlen(typedData);
                    int index = strlen(typedData)-1;

                    for (int i = index; i < len - 1; i++) {
                        typedData[i] = typedData[i + 1];
                    }
                    typedData[len - 1] = '\0';

                    remove_chars(1);
                }
            }
        }
    }
}

void _CLS() {
    /* clear screen */
    cls();
}

void _HELP() {
    /* displays all commands info */
    prints("CLS   == Clears the screen.\n");
    prints("ECHO  == Prints some text.\n");
    prints("LS    == Lists all files in the file system.\n");
    prints("MAKE  == Creates a file.\n");
}

void _ECHO(char *data) {
    /* prints text */
    prints(data);
    prints("\n");
}

void _LS() {
    /* lists all items in the filesystem */
    
    char **list = fs_list();
    int size = 0;

    while (list[size] != NULL) {
        size++;
    }

    for (int i = 0; i < size; i++) {
        prints(list[i]);
        if (i == size-1)
            break;
        prints("\n");
    }
}

void _MAKE(char *data) {
    /* creates a file */
    fs_write("", data);

    prints("File created as `");
    prints(data);
    prints("`\n");
}

void _PEAK(char *data) {
    /* reads a file and prints its data */
    char *content;
    fs_read(content, data);
    
    prints(content);
    prints("\n");
}