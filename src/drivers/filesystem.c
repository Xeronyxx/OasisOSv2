#include "filesystem.h"
#include "mem.h"
#include "print.h"

/**
 * doesn't write to the hard drive but
 * it instead writes into the memory
 * which can be used as a temporary filesystem
 * solution but one day i might upgrade it to
 * accessing the actual hard drive for permanent data store
*/

void fs_write(char *data, uint8_t datlen, char *filename) {
    char *ptr = (char *)FS_ADDRESS+fs_convert(filename);

    for (int i = 0; i < datlen; i++) {
        ptr[i] = data[i];
    }
}

void fs_read(int pointer, uint8_t datlen, char *filename) {
    char *ptr = (char *)FS_ADDRESS+fs_convert(filename);
    char data[datlen];

    for (int i = 0; i < datlen; i++) {
        data[i] = ptr[i];
    }

    char *val = (char *)pointer;
    memcpy(val, data, datlen);
}

int fs_convert(char* str) {
    int result = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        result += (int)str[i];
    }

    return result;
}