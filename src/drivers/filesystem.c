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

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char data[MAX_FILE_SIZE];
} FileEntry;

FileEntry files[MAX_FILES];
int fp = 0;

char **fs_list() {
    static char *filenames[MAX_FILES + 1];
    for (int i = 0; i < fp; i++) {
        filenames[i] = files[i].filename;
    }
    filenames[fp] = NULL;
    return filenames;
}

int fs_lookup(char *filename) {
    for (int i = 0; i < fp; i++) {
        if (strcmp(files[i].filename, filename) == 0) {
            return i;
        }
    }
    return -1;
}

void fs_write(char *data, char *filename) {
    if (strlen(data) > MAX_FILE_SIZE || fp >= MAX_FILES)
        return;

    if (strlen(filename) >= MAX_FILENAME_LENGTH)
        return;

    FileEntry newEntry;
    memcpy(newEntry.filename, filename, strlen(filename));
    memcpy(newEntry.data, data, MAX_FILE_SIZE - 1);
    newEntry.data[MAX_FILE_SIZE - 1] = '\0';

    files[fp] = newEntry;
    fp++;
}

void fs_read(char *pointer, char *filename) {
    int index = fs_lookup(filename);
    if (index == -1) return;

    memcpy(pointer, files[index].data, MAX_FILE_SIZE);
    pointer[MAX_FILE_SIZE - 1] = '\0';
}