#include "process.h"
#include "print.h"
#include "system.h"
#include "pt.h"

#include <stddef.h>

int process_count = 0;

struct Process processes[MAX_PROCESSES];
struct pt pt_threads[MAX_PROCESSES];

void START(char* name, PT_THREAD((*func)(struct pt*))) {
    if (process_count < MAX_PROCESSES) {
        processes[process_count].name = name;
        processes[process_count].id = process_count;
        processes[process_count].finished = 0;

        PT_INIT(&pt_threads[process_count]);

        if (PT_SCHEDULE(func(&pt_threads[process_count])))
            processes[process_count].finished = 0;
        else
            processes[process_count].finished = 1;

        process_count++;
    } else {
        crash(0, "Process limit reached");
    }
}

void KILL(int process_id) {
    int index = -1;
    for (int i = 0; i < process_count; i++) {
        if (processes[i].id == process_id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < process_count - 1; i++) {
            processes[i] = processes[i + 1];
            pt_threads[i] = pt_threads[i + 1];
        }
        process_count--;
    }
}