#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src,
                 int c, size_t n) {
    char *str_src = (char *) src;
    char *str_dst = (char *) dst;

    for (size_t i = 0; i < n; i++, str_src++, str_dst++) {
        *str_dst = *str_src;
        if (*str_src == (unsigned char) c)
            return str_dst + 1;
    }

    return 0;
}
