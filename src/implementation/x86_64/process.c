#include "process.h"

#define MAX_PROCESSES 150
#define false 0
#define true 1

int crashed = false;

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

        if (action != null) {
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