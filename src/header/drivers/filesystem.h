#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

#define FS_ADDRESS 0x1000

void fs_write(char *data, uint8_t datlen, char *filename);
void fs_read(int pointer, uint8_t datlen, char *filename);
int fs_convert(char* str);

#endif // FILESYSTEM_H