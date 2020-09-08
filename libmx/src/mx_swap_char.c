#include "../inc/libmx.h"

void mx_swap_char(char *s1, char *s2) {
    char str_temp = *s1;
    char str2_temp = *s2;
    *s2 = str_temp;
    *s1 = str2_temp;
}
