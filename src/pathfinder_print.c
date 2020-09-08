#include "pathfinder.h"
#include "libmx.h"

int pf_pathcmpID(int *A, int *B) {
    int min = A[0];
    if (B[0] < min)
        min = B[0];
    for (int i = 1; i < min; ++i) {
        if (A[i] != B[i])
            return A[i] - B[i];
    }
    return 0;
}

void pf_sortPathsByID(t_graph_node *node) {
    int N = 0;
    for (int i = 0; node->paths[i] != NULL; ++i) {
        N++;
    }
    int L = 0;
    int R = N - 1;
    int k = 0;
    int *tmp;
    while (L < R) {
        for (int i = L; i < R; i++)
            if (pf_pathcmpID(node->paths[i], node->paths[i + 1]) > 0) {
                tmp = node->paths[i];
                node->paths[i] = node->paths[i + 1];
                node->paths[i + 1] = tmp;
                k = i;
            }
        R = k;
        for (int i = R - 1; i >= L; i--)
            if (pf_pathcmpID(node->paths[i], node->paths[i + 1]) > 0) {
                tmp = node->paths[i];
                node->paths[i] = node->paths[i + 1];
                node->paths[i + 1] = tmp;
                k = i;
            }
        L = k + 1;
    }
}

void pf_printNodeRoutesByID(t_graph_core *graph, t_graph_node *startNode) {
    for (int i = startNode->id + 1; i < graph->real_size; ++i) {
        t_graph_node *node = pf_findNodeByID(graph, i);
        pf_sortPathsByID(node);
        for (int l = 0; node->paths[l] != NULL; ++l) {
            for (int j = 0; j < 40; ++j) {
                mx_printchar('=');
            }
            mx_printstr("\nPath: ");
            mx_printstr(startNode->name);
            mx_printstr(" -> ");
            mx_printstr(node->name);
            mx_printstr("\nRoute: ");
            mx_printstr(startNode->name);
            for (int j = 2; j < node->paths[l][0]; ++j) {
                mx_printstr(" -> ");
                mx_printstr(
                        pf_findNodeByID(graph,
                                        node->paths[l][j])->name);
            }
            mx_printstr("\nDistance: ");
            if (node->paths[l][0] > 3) {
                int prev = 0;
                int now = pf_findNodeByID(graph,
                                          node->paths[l][2])->core_data;
                mx_printint(now - prev);
                prev = now;
                for (int j = 3; j < node->paths[l][0]; ++j) {
                    mx_printstr(" + ");
                    now = pf_findNodeByID(graph,
                                          node->paths[l][j])->core_data;
                    mx_printint(now - prev);
                    prev = now;
                }
                mx_printstr(" = ");
            }
            mx_printint(node->core_data);
            mx_printchar('\n');
            for (int j = 0; j < 40; ++j) {
                mx_printchar('=');
            }
            mx_printchar('\n');
        }
    }
}

void pf_printNodeRoutes(t_graph_core *graph, t_graph_node *startNode,
                        t_graph_node *node) {
    if (!node->inf) {
        if (startNode != node) {
            if (startNode->id < node->id)
                for (int i = 0; node->paths[i] != NULL; ++i) {
                    for (int j = 0; j < 40; ++j) {
                        mx_printchar('=');
                    }
                    mx_printstr("\nPath: ");
                    mx_printstr(startNode->name);
                    mx_printstr(" -> ");
                    mx_printstr(node->name);
                    mx_printstr("\nRoute: ");
                    mx_printstr(startNode->name);
                    for (int j = 2; j < node->paths[i][0]; ++j) {
                        mx_printstr(" -> ");
                        mx_printstr(
                                pf_findNodeByID(graph,
                                                node->paths[i][j])->name);
                    }
                    mx_printstr("\nDistance: ");
                    if (node->paths[i][0] > 3) {
                        int prev = 0;
                        int now = pf_findNodeByID(graph,
                                                  node->paths[i][2])->core_data;
                        mx_printint(now - prev);
                        prev = now;
                        for (int j = 3; j < node->paths[i][0]; ++j) {
                            mx_printstr(" + ");
                            now = pf_findNodeByID(graph,
                                                  node->paths[i][j])->core_data;
                            mx_printint(now - prev);
                            prev = now;
                        }
                        mx_printstr(" = ");
                    }
                    mx_printint(node->core_data);
                    mx_printchar('\n');
                    for (int j = 0; j < 40; ++j) {
                        mx_printchar('=');
                    }
                    mx_printchar('\n');
                }
            //mx_printint(node->core_data);
        }
        node->inf = true;
        t_graph_node *buf = pf_minIDInRoadsNotInf(node);
        while (buf != NULL) {
            pf_printNodeRoutes(graph, startNode, buf);
            buf = pf_minIDInRoadsNotInf(node);
        }
    }
}

void pf_errorPrinter(t_graph_core *graph, char *filename) {
    if (!graph->err_flag)
        return;
    if (graph->err_line_invalid) {
        mx_printerr("error: line ");
        mx_printint(graph->err_line_num);
        mx_printerr(" is not valid");
    } else if (graph->err_invalid_num)
        mx_printerr("error: invalid number of islands");
    else if (graph->err_dup_bridges)
        mx_printerr("error: duplicate bridges");
    else if (graph->err_int_max)
        mx_printerr("error: sum of bridges lengths is too big");
    else if (graph->err_file_is_empty) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty");
    }
}

