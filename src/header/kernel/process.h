#ifndef PROCESS_H
#define PROCESS_H

#include "pt.h"

#define MAX_PROCESSES 256

struct Process {
    char* name;
    int id;
    int finished;
};

extern int process_count;
extern struct Process processes[];

void START(char* name, PT_THREAD((*func)(struct pt*)));
void KILL(int processId);

#endif // PROCESS_H