#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"
#include "keymap.h"
#include "terminal.h"

void kernel_main();

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
        sleep(325);
        print_str("Running on ");
        print_int(getMemorySize());
        print_str(" KB of memory.\n");
        print_str("> ");
    }

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