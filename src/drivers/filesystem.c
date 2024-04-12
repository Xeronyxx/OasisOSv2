#include "filesystem.h"
#include "mem.h"
#include "print.h"
#include "str.h"

/**
 * Doesn't write to the hard drive but
 * instead writes into the memory,
 * which can be used as a temporary filesystem
 * solution. One day it might be upgraded to
 * access the actual hard drive for permanent data storage.
*/

char *files[MAX_FILES];
int fp = 0;

char **fs_list() {
    return files;
}

int fs_lookup(char *filename) {
    for (int i = 0; i < fp; i++) {
        if (strcmp(files[i], filename) == 0) {
            return i;
        }
    }
    return -1;
}

void fs_write(char *data, char *filename) {
    if (strlen(data) > MAX_FILE_SIZE || fp >= MAX_FILES)
        return;

    char *ptr = (char *)(FS_ADDRESS + fp * MAX_FILE_SIZE);

    memcpy(ptr, data, strlen(data));
    files[fp] = filename;
    fp++;

    prints("\n");
}

void fs_read(char *pointer, char *filename) {
    int index = fs_lookup(filename);
    if (index == -1) {
        return 0;
    }

    char *ptr = (char *)(FS_ADDRESS + index * MAX_FILE_SIZE);
    memcpy(pointer, ptr, MAX_FILE_SIZE);
}