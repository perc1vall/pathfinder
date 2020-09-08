#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    char *duplicate = NULL;
    
    if (!(duplicate = mx_strnew(mx_strlen(str))))
        return NULL;
    if (!mx_strcpy(duplicate, str))
        return NULL;
    return duplicate;
}
