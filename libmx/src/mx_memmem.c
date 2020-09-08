#include "../inc/libmx.h"
// TODO error
void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len) {
    const char *beginningOfBig = big;

    while ((unsigned long)((const char *)big - beginningOfBig) < big_len) {
        char *substringToCompare =
                mx_memchr(big, *(const char *)little, big_len);

        if (substringToCompare == 0) return 0;
        if (mx_memcmp(little, substringToCompare, little_len != 0))
            continue;
        else
            return (char *)(substringToCompare);
    }
    return NULL;
}
