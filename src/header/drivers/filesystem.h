#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

#define FS_ADDRESS 0x1000

void fs_write(char *data, char *filename);
void fs_read(void *pointer, char *filename);
char** fs_list();
int fs_convert(char* str);

#endif // FILESYSTEM_H