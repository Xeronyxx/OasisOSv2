#include "keyboard.h"
#include "terminal.h"
#include "standard.h"
#include "print.h"
#include "keymap.h"

void terminal() {
    char typedData[256] = "";
    int keyPressed = false;

    prints("\n> ");

    while (1) {
        uint8_t key = scanKey();

        if (keyPressed == false) {
            keyPressed = true;

            if (key == KEY_ENTER) {
                typedData[0] = '\0';
                prints("\n> ");
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

        if (key == 0) {
            keyPressed = false;
        }
    }
}