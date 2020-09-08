#include "../inc/libmx.h"

bool mx_islower(int c) {
    return (c >= 97 && c <= 122);
}

bool mx_isdigit(int c) {
    return (c>=48&&c<=57);
}

unsigned long mx_hex_to_nbr(const char *hex) {
    int len = 0;
    for (; *(hex + len) != '\0'; ++len) {
    }
    unsigned long  base = 1;
    unsigned long dec_val = 0;
    for (int i = len - 1; i >= 0; i--) {
        char buf = hex[i];
        if (mx_islower(buf))
            buf -= 32;
        if (mx_isdigit(buf)) {
            dec_val += (buf - 48) * base;
            base = base * 16;
        } else if (buf >= 'A' && buf <= 'F') {
            dec_val += (buf - 55) * base;
            base = base * 16;
        }
    }

    return dec_val;
}

