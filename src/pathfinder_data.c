#include "pathfinder.h"
#include "libmx.h"

t_graph_core *pf_tGraphCoreInit(int fd) {
    t_graph_core *res = (t_graph_core *) malloc(sizeof(t_graph_core));
    if (res == NULL)
        return NULL;
    res->size = 0;
    res->real_size = 0;
    res->nodes = NULL;
    res->fd = fd;
    res->err_flag = false;
    res->err_file_is_empty = false;
    res->err_line_invalid = false;
    res->err_line_num = 0;
    res->err_invalid_num = false;
    res->err_dup_bridges = false;
    res->err_int_max = false;
    return res;
}

t_graph_node *pf_tGraphNodeInit(int id) {
    t_graph_node *res = (t_graph_node *) malloc(sizeof(t_graph_node));
    res->id = id;
    res->name = NULL;
    res->road_num = 0;
    res->roads = NULL;
    res->core_data = 0;
    res->inf = true;
    res->paths = NULL;
    res->core_stop = false;
    return res;
}

void pf_readFileData(t_graph_core **graph) {
    if ((*graph)->size != 0) {
        (*graph)->err_flag = true;
        return;
    }
    char *buf;

    if (mx_read_line(&buf, 1, '\n', (*graph)->fd) == -1) {
        (*graph)->err_flag = true;
        (*graph)->err_file_is_empty = true;
        return;
    }
    if (!mx_isuint(buf)) {
        (*graph)->err_flag = true;
        (*graph)->err_line_invalid = true;
        (*graph)->err_line_num = 1;
        return;
    }
    (*graph)->size = mx_atoi(buf);
    free(buf);

    (*graph)->nodes = (t_graph_node **) malloc(
            (*graph)->size * sizeof(t_graph_node *));
    for (int i = 0; i < (*graph)->size; ++i) {
        (*graph)->nodes[i] = pf_tGraphNodeInit(i);
    }
    int status = 0;
    int buf_len;
    int minus_pos;
    int comma_pos;
    int line = 1;
    t_graph_route *graphRoute = (t_graph_route *) malloc(
            sizeof(t_graph_route));
    int sum = 0;
    while (status >= 0) {
        status = mx_read_line(&buf, 1, '\n', (*graph)->fd);
        buf_len = mx_strlen(buf);
        if (buf_len == 0)
            break;                                  //todo: check error
        line++;
        minus_pos = mx_get_char_index(buf, '-');
        comma_pos = mx_get_char_index(buf, ',');
        if (minus_pos == -1 || comma_pos == -1 || comma_pos + 1 == buf_len ||
            minus_pos == 0 || minus_pos + 1 == comma_pos) {
            (*graph)->err_flag = true;
            (*graph)->err_line_invalid = true;
            (*graph)->err_line_num = line;
            free(buf);
            free(graphRoute);
            return;
        }

        char *buf1 = mx_strndup(buf, minus_pos);

        char *buf2 = mx_strndup(buf + minus_pos + 1,
                                comma_pos - minus_pos - 1);

        char *buf3 = mx_strndup(buf + comma_pos + 1, buf_len - comma_pos - 1);

        if (mx_strcmp(buf1, buf2) == 0 || !mx_isAlphebet(buf1) ||
            !mx_isAlphebet(buf2) || !mx_isuint(buf3)) {
            (*graph)->err_flag = true;
            (*graph)->err_line_invalid = true;
            (*graph)->err_line_num = line;
            return;
        }
        int buf4 = mx_atoi(buf3);
/*
        mx_printstr(buf1);
        mx_printstr(buf2);
        mx_printint(buf4);
*/
        graphRoute->dist = buf4;
        graphRoute->name1 = buf1;
        graphRoute->name2 = buf2;
        if ((sum=pf_checkOverflow(sum,buf4))==-1) {
            (*graph)->err_flag = true;
            (*graph)->err_int_max = true;
            free(buf1);
            free(buf2);
            free(buf3);
            free(buf);
            free(graphRoute);
            return;
        }
        if (!pf_addData(*graph, graphRoute))
            if ((*graph)->err_flag) {
                free(buf1);
                free(buf2);
                free(buf3);
                free(buf);
                free(graphRoute);
                return;
            }
        free(buf1);
        free(buf2);
        free(buf3);
        free(buf);
    }

    free(graphRoute);
    if ((*graph)->size != (*graph)->real_size) {
        (*graph)->err_flag = true;
        (*graph)->err_invalid_num = true;
    }
}

t_graph_node *
pf_findNodeByName(t_graph_core *graph, char *name, bool createIfNotFound) {
    for (int i = 0; i < graph->size; ++i) {
        if (graph->nodes[i]->name != NULL)
            if (mx_strcmp(graph->nodes[i]->name, name) == 0)
                return graph->nodes[i];
    }
    if (!createIfNotFound)
        return NULL;
    for (int i = 0; i < graph->size; ++i) {
        if (graph->nodes[i]->name == NULL) {
            graph->nodes[i]->name = mx_strdup(name);
            graph->real_size++;
            return graph->nodes[i];
        }
    }
    return NULL;
}

t_graph_node *pf_findNodeByID(t_graph_core *graph, int id) {
    for (int i = 0; i < graph->size; ++i) {
        if (graph->nodes[i]->id == id)
            return graph->nodes[i];
    }
    return NULL;
}

bool pf_addRoadToNode(t_graph_node *node1, t_graph_node *node2, int dist) {
    bool recursion = true;
    if (dist < 0) {
        recursion = false;
        dist *= -1;
    }
    if (node1->roads != NULL) {
        for (unsigned int i = 0; i < node1->road_num; ++i) {
            if (node1->roads[i] == node2) {
                return false;
            }
        }
    }
    if (node1->roads == NULL) {
        node1->road_num = 0;
    }
    t_graph_node **_roads = (t_graph_node **) malloc(
            sizeof(t_graph_node *) * (node1->road_num + 1));
    int *_roads_len = (int *) malloc(sizeof(int) * (node1->road_num + 1));
    for (unsigned int i = 0; i < node1->road_num; ++i) {
        _roads[i] = node1->roads[i];
        _roads_len[i] = node1->roads_len[i];
    }
    _roads[node1->road_num] = node2;
    _roads_len[node1->road_num] = dist;
    if (node1->roads != NULL) {
        free(node1->roads);
        free(node1->roads_len);
    }
    node1->roads = _roads;
    node1->roads_len = _roads_len;
    node1->road_num++;
    if (recursion)
        pf_addRoadToNode(node2, node1, -dist);
    return true;
}

bool pf_addData(t_graph_core *graph, t_graph_route *route) {
    t_graph_node *node1 = pf_findNodeByName(graph, route->name1, true);
    t_graph_node *node2 = pf_findNodeByName(graph, route->name2, true);
    if (node1 == NULL || node2 == NULL) {
        graph->err_flag = true;
        graph->err_invalid_num = true;
        return false; //todo: check error
    }
    if (!pf_addRoadToNode(node1, node2, route->dist)) {
        graph->err_flag = true;
        graph->err_dup_bridges = true;
        return false;
    }
    return true;
}

t_graph_node *pf_minIDInRoadsNotInf(t_graph_node *node) {
    int first = -1;
    for (unsigned int i = 0; i < node->road_num; ++i) {
        if (!node->roads[i]->inf) {
            first = (int) i;
            break;
        }
    }
    if (first == -1)
        return NULL;
    t_graph_node *min = node->roads[first];
    for (unsigned int i = first + 1; i < node->road_num; ++i) {
        if (!node->roads[i]->inf) {
            if (min->id > node->roads[i]->id) {
                min = node->roads[i];
            }
        }
    }
    return min;
}

void pf_freeGraph(t_graph_core *graph) {
    if (graph == NULL)
        return;
    for (int i = 0; i < graph->real_size; ++i) {
        pf_freeNode(graph->nodes[i]);
    }
    free(graph->nodes);
    graph->nodes = NULL;
    free(graph);
}

void pf_freeNode(t_graph_node *node) {
    if (node == NULL)
        return;
    if (node->name != NULL)
        free(node->name);
    node->name = NULL;
    if (node->roads != NULL)
        free(node->roads);
    node->roads = NULL;
    if (node->roads_len)
        free(node->roads_len);
    node->roads_len = NULL;
    if (node->paths != NULL) {
        int s = 0;
        for (int i = 0; node->paths[i] != NULL; ++i) {
            s++;
        }
        if (s)
            s++;
        for (int i = 0; i < s; ++i) {
            free(node->paths[i]);
        }
        free(node->paths);
    }
    node->paths = NULL;
    free(node);
}

int pf_checkOverflow(int num1, int num2) {
    if (num1 > INT_MAX - num2)
        return -1;
    else
        return num1 + num2;
}
