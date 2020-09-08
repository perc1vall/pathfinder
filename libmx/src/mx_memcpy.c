#include "../inc/libmx.h"

void *mx_memcpy(void *restrictdst, const void *restrictsrc, size_t n) {
    char *src = (char *)restrictsrc;
    char *dst = (char *)restrictdst;
    while (n-- > 0) *dst++ = *src++;
    return restrictdst;
}
