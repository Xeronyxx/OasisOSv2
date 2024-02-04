#include "print.h"
#include "standard.h"
#include "process.h"
/* #include "keyboard.h" */

int crashed = false;

void kernel_main();
void crash(int code);

int main() {
    start_process("kernel", kernel_main);
    return 0;
}

void kernel_main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
    print_str("OASIS OS. MADE BY ALBI AND XAVIER.\n");

    if (crashed == false) {
        while (1) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
                    kill_process(processes[i].id);
                    print_str("Killed process ");
                    print_int(processes[i].id);
                    print_str("\n");
                }
            }
        }
    }
    
}