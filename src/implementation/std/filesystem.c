/*
#define FILESYSTEM_START_ADDRESS 0x1000
#define FILE_CONTENTS_ADDRESS 0x2000

void fs_write(const char* data, int length) {
    char* filesystem = (char*)FILE_CONTENTS_ADDRESS;
    for (int i = 0; i < length; i++) {
        filesystem[i] = data[i];
    }
}

void fs_read(char* buffer, int length) {
    char* filesystem = (char*)FILE_CONTENTS_ADDRESS;
    for (int i = 0; i < length; i++) {
        buffer[i] = filesystem[i];
    }
}
*/
