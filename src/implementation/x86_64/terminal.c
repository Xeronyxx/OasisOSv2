#include "keyboard.h"
#include "terminal.h"
#include "standard.h"

void terminal() {
    char* typedData = "";
    int keyPressed = false;

    while (1) {
        if (keyPressed == false) {
            keyPressed = true;

            if (scanKey() == KEY_ENTER) {
                typedData = "";
                print_str("\n> ");
            }

            if (scanKey() != 0 && scanKey() != KEY_ENTER && scanKey() != KEY_BACK) {
                print_char(uint8_convert(scanKey()));
            }
            
            
            if (scanKey() == KEY_BACK) {
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

        if (scanKey() == 0) {
            keyPressed = false;
        }
    }
}