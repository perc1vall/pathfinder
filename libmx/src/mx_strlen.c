#include "../inc/libmx.h"
int mx_strlen(const char*s) {
    if (s==NULL)
        return 0;
    char a = s[0];
    int res = 0;
    while (a!='\0') {
        res++;
        a=s[res];
    }
    return res;
}
