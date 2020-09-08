#include "../inc/libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    if (*arr != NULL || delim != NULL)
        for (int i = 0; i < mx_strlen(*arr); i++) {
            mx_printstr(arr[i]);
            mx_printchar(*delim);
        }
    mx_printchar('\n');
}

