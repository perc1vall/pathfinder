#include "../inc/libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    while (*s1) {
        char *substringToCompare = mx_strchr(s1, *s2);

        if (substringToCompare == 0)
            return 0;
        if (mx_strncmp(s2, substringToCompare, mx_strlen(s2)) != 0)
            continue;
        else return substringToCompare;
    }
    return 0;
}
