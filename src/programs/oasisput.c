/**
 * Program: Oasis PUT
 * 
 * This program was made so
 * that OasisOS users could edit
 * and write to files with a text editor
*/

#include "oasisput.h"
#include "print.h"
#include "str.h"
#include "keyboard.h"
#include "standard.h"
#include "keymap.h"

void osput(char *data) {
    prints("Editing file... press CTRL to exit.\n\n");

    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_GREEN);
    prints(data);
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    char typedData[256];
    int keyPressed = false;
    int lastKey = 0x0;

    while (1) {
        int key = scanKey();

        if (key == KEY_CONTROL) { break; }
        if (key == 0x0 || key != lastKey) { keyPressed = false; }

        lastKey = key;

        if (keyPressed == false) {
            keyPressed = true;

            if (key != 0 &&
                key != KEY_BACK &&
                key != KEY_C &&
                key != KEY_CONTROL)
            {
                print_char(uint8_convert(key));
                strncat(typedData, (char[]){uint8_convert(key), '\0'}, 1);
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

    fs_write(typedData, data);
    prints("\n");
}