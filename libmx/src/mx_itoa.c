#include "../inc/libmx.h"

char *mx_itoa(int n) {
    if (n == 0) {
        char *result = (char *)malloc(2*sizeof(char ));
        result[0]='0';
        result[1]='\0';
        return result;
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
    char *result;
    if (minus == 1) {
        result = (char *)malloc((counter+2)*sizeof(char));
        result[0]='-';
        result[counter+1]='\0';
    } else {
        result = (char *)malloc((counter+1)*sizeof(char));
        result[counter]='\0';
    }
    for (int i = counter - 1; i >= 0; i--) {
        result[minus+counter-1-i]=buf[i] + '0';
    }
    return result;
}
