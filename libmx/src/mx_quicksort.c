#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    int i, j;
    char *B, *tmp;
    B = arr[(left + right) / 2];
    i = left;
    j = right;
    while (i <= j) {
        while (mx_strcmp(arr[i], B) < 0) i = i + 1;
        while (mx_strcmp(arr[j], B) > 0) j = j - 1;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i = i + 1;
            j = j - 1;
        }
    }
    if (left < j) return mx_quicksort(arr, left, j) + 1;
    if (i < right) return mx_quicksort(arr, i, right) + 1;
    return 1;
}
