struct Process {
    const char* name;
    int id;
    int finished;
};

void START(const char* name, void (*action));
void KILL(int processId);