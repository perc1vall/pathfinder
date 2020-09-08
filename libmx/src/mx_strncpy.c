#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    char *sourcecopy = (char *)src;
    for (int i = 0; i < len; i++) {
        *dst = *sourcecopy;
        dst++;
        sourcecopy++;
    }
    return (dst - len);
}
