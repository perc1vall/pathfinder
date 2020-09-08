#include "../inc/libmx.h"


char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long quotient, remainder;
    int i, j = 0;
    char hexadecimal[100];

    quotient = nbr;

    while (quotient != 0) {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimal[j++] = 48 + remainder;
        else
            hexadecimal[j++] = 87 + remainder;
        quotient = quotient / 16;
    }

    char *returnString = mx_strnew(j);

    int k = 0;

    for (i = j - 1; i >= 0; i--) {
        returnString[k] = hexadecimal[i];
        k++;
    }
    return returnString;
}
