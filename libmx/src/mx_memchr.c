#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *str= (char *) s;
    for (size_t i = 0; i < n; i++, str++) {
        if (*str== (unsigned char) c) {
            return str;
        }
    }
    return 0;
}
