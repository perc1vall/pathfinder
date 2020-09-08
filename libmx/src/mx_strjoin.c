#include "../inc/libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    int len = mx_strlen(s1) + mx_strlen(s2);
    if (len == 0)
        return NULL;
    char *joined = mx_strnew(len);
    if (joined == NULL)
        return NULL;
    if (s1 == NULL) {
        mx_strcat(joined,s2);
    } else if (s2 == NULL) {
        mx_strcat(joined,s1);
    } else {
        mx_strcat(joined,s1);
        mx_strcat(joined,s2);
    }
    return joined;
}
