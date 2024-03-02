/*
#define FILESYSTEM_START_ADDRESS 0x1000
#define FILE_CONTENTS_ADDRESS 0x2000

void write_to_filesystem(const char* data, int length) {
    char* filesystem = (char*)FILE_CONTENTS_ADDRESS;
    for (int i = 0; i < length; i++) {
        filesystem[i] = data[i];
    }
}

void read_from_filesystem(char* buffer, int length) {
    char* filesystem = (char*)FILE_CONTENTS_ADDRESS;
    for (int i = 0; i < length; i++) {
        buffer[i] = filesystem[i];
    }
}

int main() {
    const char* data_to_write = "Hello, World!";
    int data_length = strlen(data_to_write);

    write_to_filesystem(data_to_write, data_length);

    char buffer[256];

    read_from_filesystem(buffer, data_length);

    printf("Data read from filesystem: %s\n", buffer);

    return 0;
}
*/