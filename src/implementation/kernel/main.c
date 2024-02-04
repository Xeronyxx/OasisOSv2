#include "print.h"
#include "process.h"
/* #include "keyboard.h" */

void START(const char* name, void (*action)());
void KILL(int processId);
void kernel_main();
void test();
void crash(int code);

int main() {
    kernel_main();
    return 0;
}

void kernel_main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_LIGHT_RED, PRINT_COLOUR_BLACK);
    print_str("OASIS OS. MADE BY XAVIER AND ALBI.\n");

    START("test", test);

    if (crashed == false) {
        while (1) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
                    KILL(processes[i].id);
                    print_str("Killed process ");
                    print_int(processes[i].id);
                    print_str("\n");
                }
            }
        }
    }
}

void test() {
    print_str("This is a process.\n");
}