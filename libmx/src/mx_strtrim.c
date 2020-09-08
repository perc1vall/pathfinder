#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL)
        return NULL;
    int start = 0, end = mx_strlen(str) - 1;
    for (; (str[start] >= 9 && str[start] < 13) || str[start] == 32; start++) {
    }
    for (; (str[end] >= 9 && str[end] < 13) || str[end] == 32; end--) {
    }
    int len = end - start + 1;
    if (len == 0)
        return NULL;
    return mx_strndup(str + start, len);
}
