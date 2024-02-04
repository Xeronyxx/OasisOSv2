#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
/* #include "keyboard.h" */

void kernel_main();

int main() {
<<<<<<< HEAD
    start_process("kernel", kernel_main);
=======
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
>>>>>>> bd7c7f7f99d869224c71a8796d5a3b07effe589c
    return 0;
}

void kernel_main() {
    print_str("OASIS OS. MADE BY ALBI AND XAVIER.\n");

    if (crashed == false) {
        while (1) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
<<<<<<< HEAD
                    kill_process(processes[i].id);
                    print_str("Killed process ");
=======
                    KILL(processes[i].id);
>>>>>>> bd7c7f7f99d869224c71a8796d5a3b07effe589c
                    print_int(processes[i].id);
                    print_str("\n");
                }
            }
        }
    }
    
}