#include "../inc/libmx.h"
char **mx_strsplit(const char *s, char c) {
    int arr = mx_count_words(s, c);
    char **result =
            (char **)malloc(sizeof(char *) * (arr + 1));  // videlaem pamat
    result[arr] = 0;

    if (s == 0) return 0;
    for (int p = 0; p < arr; p++) {
        while (*s == c) {
            s++;
        }
        char *i = (char *)s;
        int j = 0;
        while (*s != c) {
            j++;
            s++;
        }
        char *word = mx_strnew(j);
        mx_strncpy(word, i, j);
        result[p] = word;
    }
    return result;
}
