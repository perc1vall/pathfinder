#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (list == NULL)
        return;
    t_list *new = mx_create_node(data);
    t_list *buf = *list;
    if (buf != NULL) {
        while (buf->next != NULL) {
            buf = buf->next;
        }
        buf->next = new;
    } else *list = new;
}
