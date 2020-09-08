#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL)
        return -2;
    int id = 0;
    while (str[id] != '\0') {
        if (str[id] == c)
            return id;
        id++;
    }
    return -1;
}
