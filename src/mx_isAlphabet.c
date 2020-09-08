#include "pathfinder.h"
#include "libmx.h"

bool mx_isAlphebet (char *str) {
    if (str==NULL)
        return false;
    for (int i = 0; i < mx_strlen(str); i++) {
        if ((str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z')) {
            return false;
        }
    }
    return true;
}
