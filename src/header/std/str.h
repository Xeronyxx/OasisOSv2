#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <stdint.h>

char *strncat(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strsub(const char* str, int len);
size_t strlen(const char *str);
int strcmp(char *str, char *comp);
int strncmp(char *str, char *comp, uint8_t n);

#endif // STR_H