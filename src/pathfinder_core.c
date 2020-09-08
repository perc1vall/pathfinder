#include "pathfinder.h"
#include "libmx.h"

void pf_shortWaysCore(t_graph_core *graph) {
    if (graph->real_size <= 1)
        return;
    for (int i = 0; i < graph->real_size; ++i) {
        graph->nodes[i]->inf = false;
        graph->nodes[i]->paths = (int **) malloc(sizeof(int *) * 2);
        graph->nodes[i]->paths[0] = (int *) malloc(sizeof(int) * 2);
        graph->nodes[i]->paths[0][0] = 2;
        graph->nodes[i]->paths[0][1] = graph->nodes[i]->id;
        graph->nodes[i]->paths[1] = NULL;
        pf_sWCAlgorithm(graph->nodes[i]);
        pf_printNodeRoutesByID(graph, graph->nodes[i]);
        pf_sWCreload(graph);
    }
}

void pf_sWCreload(t_graph_core *graph) {
    for (int i = 0; i < graph->real_size; ++i) {
        graph->nodes[i]->core_data = 0;
        graph->nodes[i]->inf = true;
        if (graph->nodes[i]->paths != NULL) {
            int s = 0;
            for (int j = 0; graph->nodes[i]->paths[j] != NULL; ++j) {
                s++;
            }
            if (s)
                s++;
            for (int j = 0; j < s; ++j) {
                free(graph->nodes[i]->paths[j]);
            }
            free(graph->nodes[i]->paths);
        }
        graph->nodes[i]->paths = NULL;
        graph->nodes[i]->core_stop = false;
    }
}

t_graph_node *pf_sWCMinNotStopped(t_graph_node *node) {
    int first = -1;
    for (unsigned int i = 0; i < node->road_num; ++i) {
        if (!node->roads[i]->core_stop) {
            first = (int) i;
            break;
        }
    }
    if (first == -1)
        return NULL;
    t_graph_node *min = node->roads[first];
    for (unsigned int i = first + 1; i < node->road_num; ++i) {
        if (!node->roads[i]->core_stop) {
            if (min->core_data > node->roads[i]->core_data) {
                min = node->roads[i];
            }
        }
    }
    return min;
}

void pf_sWCaddPath(t_graph_node *node, int target) {
    int paths_node = 0;
    for (int i = 0; node->paths[i] != NULL; ++i) {
        paths_node++;
    }
    int paths_target = 0;
    if (node->roads[target]->paths != NULL)
        for (int i = 0; node->roads[target]->paths[i] != NULL; ++i) {
            paths_target++;
        }
    int *paths_target_copied = (int *) malloc(sizeof(int) * (paths_target));
    paths_target = 0;
    if (node->roads_len[target] + node->core_data ==
        node->roads[target]->core_data) {
        for (int i = 0; node->roads[target]->paths[i] != NULL; ++i) {
            bool inc = false;
            for (int j = 0; j < paths_node; ++j) {
                if (node->roads[target]->paths[i][0] - 1 ==
                    node->paths[j][0]) {
                    inc = false;
                    for (int k = 1;
                         k < node->roads[target]->paths[i][0] - 1; ++k) {
                        if (node->roads[target]->paths[i][k] !=
                            node->paths[j][k]) {
                            inc = true;
                            break;
                        }
                    }
                    if (!inc)
                        break;

                }
            }
            if (!inc) {
                inc = true;
                for (int j = 0; j < paths_node; ++j) {
                    if (node->roads[target]->paths[i][0] - 1 ==
                        node->paths[j][0]) {
                        inc = false;
                    }
                }
            }
            if (inc) {
                paths_target_copied[paths_target] = i;
                paths_target++;
            }
        }
    }
    int **buf = (int **) malloc(
            sizeof(int *) * (paths_node + paths_target + 1));
    buf[paths_node + paths_target] = NULL;
    for (int i = 0; i < paths_node; ++i) {
        buf[i] = (int *) malloc(sizeof(int) * (node->paths[i][0] + 1));
        buf[i][0] = node->paths[i][0] + 1;
        for (int j = 1; j < node->paths[i][0]; ++j) {
            buf[i][j] = node->paths[i][j];
        }
        buf[i][node->paths[i][0]] = node->roads[target]->id;
    }
    for (int i = 0; i < paths_target; ++i) {
        buf[i + paths_node] = (int *) malloc(
                sizeof(int) *
                (node->roads[target]->paths[paths_target_copied[i]][0]));
        for (int j = 0;
             j < node->roads[target]->paths[paths_target_copied[i]][0]; ++j) {
            buf[i +
                paths_node][j] = node->roads[target]->paths[paths_target_copied[i]][j];
        }
    }

    if (node->roads_len[target] + node->core_data !=
        node->roads[target]->core_data && node->roads[target]->core_data != 0)
        for (int i = 0; node->roads[target]->paths[i] != NULL; ++i) {
            paths_target++;
        }
    if (paths_target != 0)
        for (int i = 0; i <= paths_target; ++i) {
            free(node->roads[target]->paths[i]);
        }
    free(node->roads[target]->paths);
    node->roads[target]->paths = buf;
    node->roads[target]->core_data = node->core_data + node->roads_len[target];
    if (node->roads[target]->inf)
        node->roads[target]->inf = false;
}

void pf_sWCAlgorithm(t_graph_node *start) {
    for (unsigned int i = 0; i < start->road_num; ++i) {
        if (start->roads[i]->inf ||
            (start->roads_len[i] + start->core_data <=
             start->roads[i]->core_data)) {
            pf_sWCaddPath(start, (int) i);
            start->roads[i]->core_stop = false;
        }
    }
    start->core_stop = true;
    t_graph_node *buf = pf_sWCMinNotStopped(start);
    while (buf != NULL) {
        pf_sWCAlgorithm(buf);
        buf = pf_sWCMinNotStopped(start);
    }
}
