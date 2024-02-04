#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"

void kernel_main();
int keyPressed = false;

int main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    if (crashed == false) {
        print_clear();
        print_str("OASIS OS. `APPRECIATE THE SOFTWARE`\n");
        print_str("Running on ");
        print_int(getMemorySize());
        print_str(" KB of memory.\n");
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

        if (scanKey() == KEY_R && keyPressed == false) {
            keyPressed = true;
            print_str("NAME                       PID\n");
            for (int i = 0; i < processCount; i++) {
                print_str(processes[i].name);

                int zerosNeeded = 25 - strlen(processes[i].name);
                for (int j = 0; j < zerosNeeded; j++) {
                    print_char(' ');
                }

                print_int(processes[i].id);
                print_char('\n');
            }
        }

        if (scanKey() == 0 && keyPressed == true) {
            keyPressed = false;
        }
    }
}