#include <stddef.h>
#include <stdlib.h>
#include "standard.h"

size_t strlen(const char *str) {
    size_t length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

int strcmp(const char* str1, const char* str2){
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}

void strcpy(char *dest, const char *src){
    while (*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }

    *dest += '\0';
}

void strncpy(char *dest, const char *src, size_t n){
    while (*src != '\0' && n > 0){
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    if (n > 0){
        *dest = '\0';
    }
}

char** strtok(const char* str, char delim, size_t* count){
    size_t delimiters = 0;
    size_t strLen = strlen(str);

    for (size_t i = 0; i < strLen; i++){
        if (str[i] == delim){
            delimiters++;
        }
    }

    char** res = (char**)malloc((delimiters + 1) * sizeof(char));

    size_t tokenIdx = 0;
    size_t tokenStrt = 0;

    for (size_t i = 0; i <= strLen; i++){
        if (str[i] == delim || str[i] == '\0'){
            res[tokenIdx] = (char*)malloc((i - tokenStrt + 1) * sizeof(char));

            strncpy(res[tokenIdx], str + tokenStrt, i - tokenStrt);
            res[tokenIdx][i - tokenStrt] = '\0';

            tokenIdx++;
            tokenStrt = i + 1;
        }
    }

    *count = delimiters + 1;

    return res;
}