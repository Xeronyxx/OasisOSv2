#include <stddef.h>
#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"
#include "keymap.h"
#include "terminal.h"

void kernel_main();

int main() {
    cls();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    crash(6942, "sEX");

    if (crashed == false) {
        prints("OASIS OS. ``APPRECIATE THE SOFTWARE``\n");
        sleep(325);
        prints("Running on ");
        print_int(getMemorySize());
        prints(" KB of memory.\n\n");
        prints("> ");

        START('terminal', terminal);

        while (1) {
            if (crashed == true) {
                break;
            }

            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
                    KILL(processes[i].id);
                }
            }
        }
    }
}