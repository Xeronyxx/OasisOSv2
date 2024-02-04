#define MAX_PROCESSES 150
#pragma once

struct Process {
    const char* name;
    int id;
    int finished;
};

extern int processCount; 
extern struct Process processes[MAX_PROCESSES];

void START(const char* name, void (*action)());
void KILL(int processId);