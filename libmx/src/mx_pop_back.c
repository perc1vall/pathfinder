#include "../inc/libmx.h"

void mx_pop_back(t_list **list) {
    if (list == NULL)
        return;
    if (*list == NULL) {
        return;
    }
    if ((*list)->next == NULL) {
        mx_pop_front(list);
        return;
    }
    t_list *node = *list;
    while (node->next->next != NULL) {
        node=node->next;
    }
    free(node->next);
    node->next=NULL;
}
