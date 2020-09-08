#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    if (size < 0)
        return NULL;
    char *res = (char *) malloc((size + 1) * sizeof(char));
    if (res == NULL)
        return NULL;
    for (int i = 0; i < size + 1; ++i) {
        res[i] = '\0';
    }
    return res;
}

