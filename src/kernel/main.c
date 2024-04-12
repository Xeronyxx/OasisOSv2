#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"
#include "keymap.h"
#include "terminal.h"
#include "str.h"
#include "filesystem.h"
#include <stddef.h>

void kernel_main();

int main() {
    cls();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    if (crashed == false) {
        prints("OASIS OS. ``APPRECIATE THE SOFTWARE``\n");  
        prints("Running on ");
        printi(getMemorySize());
        prints(" KB of memory.\n");

        char code[] = "PRINT\nTHANK YOU FOR USING OASIS OS";
        fs_write(code, "WELCOME.OASIS");

        START("terminal", terminal);

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
