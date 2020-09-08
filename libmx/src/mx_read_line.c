#include "../inc/libmx.h"

//TODO error
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static size_t last_del = 0;
    if (buf_size == 0)
        return -2;
    *lineptr = NULL;
    buf_size = 1;
    char *buf = (char *) malloc((buf_size + 1) * sizeof(char));
    char *res = NULL;
    buf[buf_size] = '\0';
    char *buf_res = NULL;
    size_t prev_last_del = last_del;
    int iter = last_del;
    buf[0] = '\0';
    while (1) {
        read(fd, buf, buf_size);
        if (mx_strlen(buf) == 0) {
            if (res == NULL || (unsigned) iter == last_del)
                break;
            iter += 0;
            last_del = iter;
            *lineptr = res;
            free(buf);
            return (int) (last_del - prev_last_del);
        }
        for (int i = 0; i < mx_strlen(buf); ++i) {
            if (buf[i] == delim) {
                iter += i;
                last_del = iter;
                *lineptr = res;
                free(buf);
                return (int) (last_del - prev_last_del);
            }
        }
        buf_res = mx_strjoin(res, buf);
        free(res);
        res = buf_res;
        iter += buf_size;
        buf[0] = '\0';
    }
    free(buf);
    return -1;
}

