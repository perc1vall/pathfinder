#include "../inc/libmx.h"

char *
mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;
    char *res = NULL;
    char *buf_res;
    char *buf_str;
    int len = 0;
    int pos_str = 0;
    int sub_len = mx_strlen(sub);
    int id = -sub_len;
    while (1) {
        if (mx_get_substr_index(str + id + sub_len, sub) == -1) {
            buf_res = mx_strjoin(res, str+id+sub_len);
            free(res);
            res = buf_res;
            break;
        }
        id = mx_get_substr_index(str + id + sub_len, sub)+id+sub_len;
        buf_str = mx_strndup(str + pos_str, id - pos_str);
        buf_res = mx_strjoin(res, buf_str);
        free(res);
        res = buf_res;
        pos_str = id + sub_len;
        len += id - pos_str;
        buf_res = mx_strjoin(res, replace);
        free(res);
        res = buf_res;
    }
    return res;
}
