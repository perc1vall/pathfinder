#include "pathfinder.h"
#include "libmx.h"

int mx_atoi(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int len = 0;
    char *buf = (char *) str;
    while (*buf != '\0' && ((*buf >= 9 && *buf <= 13) || (*buf == 32))) {
        buf++;
    }
    if (*buf == '\0') return 0;
    char *buf1 = buf;
    int minus = 0;
    while (*buf != '\0' &&
           ((*buf > 47 && *buf < 58) || (*buf == 45 && minus == 0))) {
        if (*buf == 45) {
            minus = 1;
            len--;
        }
        len++;
        buf++;
    }
    int res = 0;
    for (int i = 0; i < len; ++i) {
        int dig = 1;
        for (int j = 0; j < len - 1 - i; ++j) {
            dig *= 10;
        }
        res += ((*(buf1 + minus) - '0') * dig);
        buf1++;
    }
    if (minus)
        res *= -1;
    return res;
}
