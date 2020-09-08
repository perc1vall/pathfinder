#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL)
        return NULL;
    int new_length = 0;
    bool space = true;
    for (int i = 0; i < mx_strlen(str); ++i) {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32) {
            if (!space) {
                new_length++;
                space = true;
            }
        } else {
            new_length++;
            if (space)
                space = false;
        }
    }
    if (space)
        new_length--;
    int set_length = new_length;
    char *new_str = (char *) malloc(sizeof(char) * (new_length + 1));
    if (new_str==NULL)
        return NULL;
    new_str[new_length] = '\0';
    if (!space)
        space = true;
    new_length=0;
    for (int i = 0; i < mx_strlen(str); ++i) {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32) {
            if (!space) {
                new_str[new_length]=' ';
                new_length++;
                space = true;
            }
        } else {
            new_str[new_length]=str[i];
            new_length++;
            if (space)
                space = false;
        }
        if (set_length==new_length)
            break;
    }
    return new_str;
}
