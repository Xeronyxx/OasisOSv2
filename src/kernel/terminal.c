#include "keyboard.h"
#include "terminal.h"
#include "standard.h"
#include "str.h"
#include "print.h"
#include "keymap.h"
#include "filesystem.h"
#include "system.h"

#include "oasisput.h"

void _CLS();
void _HELP();
void _LS();
void _OASIS();

void _ECHO(char *data);
void _MAKE(char *data);
void _PEEK(char *data);
void _PUT(char *data);

PT_THREAD(terminal(struct pt* pt)) {
    char typedData[256] = "";
    int keyPressed = false;
    int lastKey = 0x0;

    char lastcmd[256] = "";

    prints("\n> ");

    while (1) {
        uint8_t key = scan_key();

        if (key == 0 || key != lastKey) {
            keyPressed = false;
        }

        if (keyPressed == false) {
            keyPressed = true;
            lastKey = key;

            if (key == KEY_UP && strcmp(typedData, lastcmd) != 0) {
                arrclear(typedData, 256);
                strncat(typedData, lastcmd, 256);
                prints(typedData);
            }

            if (key == KEY_ENTER) {
                prints("\n");

                char *arg;

                arrclear(lastcmd, 256);
                strncat(lastcmd, typedData, 256);

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
                } else if (strncmp(typedData, "SHUTDOWN", 8) == 0) {
                    sysexit();
                } else if (strncmp(typedData, "PEEK", 4) == 0) {
                    arg = strsub(typedData, 5);
                    _PEEK(arg);
                } else if (strcmp(typedData, "OASIS") == 0) {
                    _OASIS();
                } else if (strncmp(typedData, "PUT", 3) == 0) {
                    arg = strsub(typedData, 4);
                    _PUT(arg);
                } else if (strlen(typedData) != 0) {
                    prints("Invalid command, type `HELP` for command info.\n");
                }

                typedData[0] = '\0';
                prints("> ");
            }

            if (key != 0 && key != KEY_ENTER && key != KEY_BACK) {
                print_char(uint8_convert(key));
                strncat(typedData, (char[]){uint8_convert(scan_key()), '\0'}, 1);
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
    prints("CLS        == Clears the screen.\n");
    prints("ECHO    <> == Prints some text.\n");
    prints("LS         == Lists all files in the file system.\n");
    prints("MAKE    <> == Creates a file.\n");
    prints("PEEK    <> == Views a file.\n");
    prints("RUN     <> == Runs a compiled OasisLang file.\n");
    prints("OASIS      == Shows OS info.\n");
    prints("PUT     <> == Writes data to a file.\n");
    prints("HELP       == Shows this screen.\n");
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
        prints("\n");
    }
}

void _MAKE(char *data) {
    /* creates a file */
    fs_write("...", data);

    prints("File created as `");
    prints(data);
    prints("`\n");
}

void _PEEK(char *data) {
    /* reads a file and prints its data */
    char content[256];
    fs_read(content, data);
    
    prints(content);
    prints("\n");
}

void _OASIS() {
    /* gives os info */
    prints("VERSION: 1.1\nPUBLISHED: July 10th 2024\n");
}

void _PUT(char *data) {
    /* writes data to a file */
    osput(data);
}