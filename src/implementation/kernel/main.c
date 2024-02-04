#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"

void kernel_main();
int keyPressed = false;

char* typedData = "";

int main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    if (crashed == false) {
        print_clear();
        print_str("OASIS OS. ``APPRECIATE THE SOFTWARE``\n");
        print_str("Running on ");
        print_int(getMemorySize());
        print_str(" KB of memory.\n");
        crash(69);
        print_str("> ");
    }

    while (1) {
        if (crashed == true) {
            break;
        }

        for (int i = 0; i < processCount; i++) {
            if (processes[i].finished) {
                KILL(processes[i].id);
            }
        }

        if (scanKey() == KEY_ENTER && keyPressed == false) {
            keyPressed = true;
            typedData = "";
            print_str("\n> ");
        }

        if (scanKey() == 0 && keyPressed == true) {
            keyPressed = false;
        }
    }
}