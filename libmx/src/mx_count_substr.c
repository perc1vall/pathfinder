#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int i = 0;

    if (str == NULL || sub == NULL) {
        return -1;
    }
    if (mx_strlen(sub) <= 0) {
        return 0;
    }

    while (*str) {
        if (mx_memcmp(str, sub, mx_strlen(sub)) == 0) {
            i++;
        }
        str++;
    }
    return i;
}

