#include "../inc/libmx.h"

void mx_pop_front(t_list **list) {
    if (list == NULL)
        return;
    if (*list == NULL) {
        return;
    }
    t_list *node = *list;
    *list = node->next;
    free(node);
}
