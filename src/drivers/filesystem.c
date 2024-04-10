#include "filesystem.h"
#include "mem.h"
#include "print.h"
#include "str.h"

/**
 * doesn't write to the hard drive but
 * it instead writes into the memory
 * which can be used as a temporary filesystem
 * solution but one day i might upgrade it to
 * accessing the actual hard drive for permanent data store
*/

char *files[] = { NULL };
int fp = 0;

char **fs_list() {
    return files;
}

void fs_write(char *data, char *filename) {
    char *ptr = (char *)FS_ADDRESS+fs_convert(filename);
    int i = 0;

    for (; i < strlen(data); i++) {
        ptr[i] = data[i];
    }
    ptr[i+1] = "\0"; // null terminator

    files[fp] = filename;
    fp++;
}

void fs_read(void *pointer, char *filename) {
    char *ptr = (char *)FS_ADDRESS + fs_convert(filename);
    char data[256];

    int i;
    for (i = 0; ptr[i] != '\0'; i++) {
        data[i] = ptr[i];
    }
    data[i] = '\0';

    memcpy(pointer, data, strlen(data) + 1);
}

int fs_convert(char* str) {
    int result = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        result += (int)str[i];
    }

    return result;
}