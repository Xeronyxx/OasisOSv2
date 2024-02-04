#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
/* #include "keyboard.h" */

void kernel_main();

int main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    print_str("OASIS OS. MADE BY XAVIER AND ALBI.\n");

    while (1) {
        if (crashed == false) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
                    KILL(processes[i].id);
                    print_int(processes[i].id);
                    print_str("\n");
                }
            }
        }
    }
    
}