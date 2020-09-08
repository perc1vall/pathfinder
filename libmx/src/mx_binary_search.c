#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int l = 0;
    int r = size - 1;
    int i;
    while (l <= r) {
        (*count)++;
        i = (r + l) / 2;
        if (mx_strcmp(arr[i], s) > 0)
            r = i - 1;
        if (mx_strcmp(arr[i], s) < 0)
            l = i + 1;
        if (mx_strcmp(arr[i], s) == 0)
            return i;
    }
    *count = 0;
    return -1;
}
