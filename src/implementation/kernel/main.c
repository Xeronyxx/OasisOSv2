#include "print.h"
/* #include "keyboard.h" */

#define MAX_PROCESSES 150
#define false 0
#define true 1

int crashed = false;

struct Process {
    const char* name;
    int id;
    int finished;
};

int processCount = 0;
struct Process processes[MAX_PROCESSES];

void START(const char* name, void (*action)());
void KILL(int processId);
void kernel_main();
void test();
void crash(int code);

int main() {
    kernel_main();
    return 0;
}

void START(const char* name, void (*action)()) {
    print_str("Starting process\n");
    if (processCount < MAX_PROCESSES) {
        processes[processCount].name = name;
        processes[processCount].id = processCount + 1;
        processes[processCount].finished = 0;
        processCount++;

        print_str("PID: ");
        print_int(processCount-1);
        print_str("\n");

        if (action != NULL) {
            action();
        }

        processes[processCount - 1].finished = 1;
    } else {
        crash(100);
    }
}

void KILL(int processId) {
    int index = -1;
    for (int i = 0; i < processCount; i++) {
        if (processes[i].id == processId) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < processCount - 1; i++) {
            processes[i] = processes[i + 1];
        }
        processCount--;
    }
}

void kernel_main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
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

void crash(int code) {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);
    print_str("SYSTEM HAS CRASHED. CODE: ");
    print_int(code);
    print_str(". \nPRESS ENTER TO EXIT.");

    /*while (1) {
        if (keyboard_enabled() == true) {
            if (keyboard_get_key() == "\n") {
                break;
            }
        } else {
            break;
        }
    }*/
}