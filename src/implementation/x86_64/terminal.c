#include "keyboard.h"
#include "terminal.h"
#include "standard.h"
#include "print.h"
#include "keymap.h"

int cursorVisible = 1;
const int cursorBlinkRate = 500; // ms

void terminal() {
    char typedData[256] = "";
    int keyPressed = false;
    // int cursorTimer = 0;

    while (1) {
        uint8_t key = scanKey();

        if (keyPressed == false) {
            // if (cursorVisible){
            //     remove_chars(1);
            //     cursorVisible = 0;
            // }
            keyPressed = true;

            if (key == KEY_ENTER) {
                command(typedData);
                typedData[0] = '\0';
                print_str("\n> ");
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

            // cursorTimer = 0;
        }

        if (key == 0) {
            keyPressed = false;
        }

        // if (cursorTimer >= cursorBlinkRate){
        //     toggleCursor();
        //     cursorTimer = 0;
        // }
    }
}

// void toggleCursor(){
//     cursorVisible = 1 - cursorVisible;

//     if (cursorVisible){
//         print_char('_');
//     } else {
//         remove_chars(1);
//     }
// }

void command(char* command){
    int count = 0;
    char** tkns = strtok(command, ' ', count);

    
}