#include "pathfinder.h"
#include "libmx.h"

bool mx_isuint (char *str) {
    if (str==NULL)
        return false;
    for (int i = 0; i < mx_strlen(str); i++) {
        if ((i == 0 && (str[i] < '1' || str[i] > '9')) ||
            (str[i] < '0' || str[i] > '9')) {
            return false;
        }
    }
    return true;
}
