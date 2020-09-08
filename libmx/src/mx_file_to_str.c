#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    int counter = 0;
    int buf = 0;
    int n = 0;
    buf = open(filename, O_RDONLY);
    char bufread;

    if (buf == -1) {
        return NULL;
    }
    while ((n = read(buf, &bufread, 1) != 0)) {
        counter++;
    }
    close(buf);
    buf = open(filename, O_RDONLY);
    char *res = mx_strnew(counter);
    char *start = res;
    for (int i = 0; i < counter; i++) {
        read(buf, res, 1);
        res++;
    }
    close(buf);
    return start;
}

