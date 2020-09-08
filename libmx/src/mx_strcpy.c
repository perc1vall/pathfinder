#include "../inc/libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    char *tmp = (char *) src;
    char *tmp1 = dst;
    while (*tmp != '\0')
        *(dst++) = *(tmp++);
    *dst = '\0';
    return tmp1;
}
