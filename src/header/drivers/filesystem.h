#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

#define FS_ADDRESS 0xFF
#define MAX_FILES 100
#define MAX_FILE_SIZE 255
#define MAX_FILENAME_LENGTH 20

void fs_write(char *data, char *filename);
void fs_read(char *pointer, char *filename);
int fs_lookup(char *filename);
char** fs_list();

#endif // FILESYSTEM_H