#include <stddef.h>
#pragma once

#define false 0
#define true 1

size_t strlen(const char *str);
char *strncat(char *dest, const char *src, size_t n);