#include "../inc/libmx.h"

void mx_printint(int n) {
    if (n == 0) {
        mx_printchar('0');
        return;
    }
    int ultralow = 0;
    int minus = 0;
    if (n < 0) {
        minus = 1;
        if (n != -2147483648)
            n *= -1;
        else {
            n += 1;
            n *= -1;
            ultralow = 1;
        }
    }
    int buf[25];
    int counter = 0;
    while (n != 0) {
        buf[counter] = n % 10;
        n /= 10;
        counter++;
    }
    if (ultralow == 1)
        buf[0] = 8;
    if (minus == 1)
        mx_printchar('-');
    for (int i = counter - 1; i >= 0; i--) {
        mx_printchar(buf[i] + '0');
    }
}
