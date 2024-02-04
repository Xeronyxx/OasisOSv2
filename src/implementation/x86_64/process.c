#include "process.h"
#include "print.h"
#include "system.h"
#include <stddef.h>

<<<<<<< HEAD
int processCount = 0;
struct Process processes[MAX_PROCESSES];

void start_process(const char* name, void (*action)()) {
    print_str("Starting process\n");
=======
int processCount = 1;
struct Process processes[MAX_PROCESSES];

void START(const char* name, void (*action)()) {
>>>>>>> bd7c7f7f99d869224c71a8796d5a3b07effe589c
    if (processCount < MAX_PROCESSES) {
        processes[processCount].name = name;
        processes[processCount].id = processCount + 1;
        processes[processCount].finished = 0;
        processCount++;

        if (action != NULL) {
            action();
        }

        processes[processCount - 1].finished = 1;
    } else {
        crash(100);
    }
}

void kill_process(int processId) {
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