#pragma once

#define MAX_PROCESSES 150

struct Process {
    char* name;
    int id;
    int finished;
};

extern int processCount;
extern struct Process processes[];

void START(char* name, void (*action)());
void KILL(int processId);