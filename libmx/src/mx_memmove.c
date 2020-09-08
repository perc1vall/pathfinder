#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *to = dst;
    const char *sourse = src;
    const char *i;
    char *j;

    if (len < 0) return NULL;

    if (to < sourse) {
        while (len--) *to++ = *sourse++;
    } else {
        i = sourse + (len - 1);
        j = to + (len - 1);
        while (len--) *j-- = *i--;
    }
    return (dst);
}
