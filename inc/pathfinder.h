#ifndef CLION_PROJECT_PATHFINDER_H
#define CLION_PROJECT_PATHFINDER_H

#include "libmx.h"
#include <limits.h>

typedef struct s_graph_node {
    int id;                     //порядковий номер
    char *name;                 //назва вершини

    unsigned int road_num;      //кількість дуг
    struct s_graph_node **roads;//вказівники на вершини з'єднані дугою
    int *roads_len;             //масив довжин дуг

    int core_data;              //показник алгоритму (відстань від початкової точки)
    bool inf;                   //показник алгоритму (нескінченність)
    int **paths;                //зареєстровані найкоротші маршрути (NULL в кінці)
    //на початку int масивів
    // перший елемент - кількість елементів масиву
    //далі id вузлів які складають шлях

    bool core_stop;             //показник алгоритму (якщо алгоритм тут вже був)
} t_graph_node;

typedef struct s_graph_core {
    int size;                   //кількість вершин
    int real_size;
    t_graph_node **nodes;       //масив вказівників на вершини

    int fd;                     //файл з якого зчитано

    bool err_flag;              //прапор помилки основний (вказувати обов'язково при будь-якій помилці)
    bool err_file_is_empty;
    bool err_line_invalid;
    int err_line_num;           //вказувати, якщо err_line_invalid == true
    bool err_invalid_num;
    bool err_dup_bridges;
    bool err_int_max;
} t_graph_core;

typedef struct s_graph_route {
    char *name1;
    char *name2;
    int dist;
} t_graph_route;

/*additional functions*/

void mx_printerr(const char *s);

bool mx_isuint(char *str);

bool mx_isAlphebet(char *str);

int mx_atoi(const char *str);

/*pathfinder_data.c*/

t_graph_core *pf_tGraphCoreInit(int fd);

void pf_readFileData(t_graph_core **graph);

bool pf_addData(t_graph_core *graph, t_graph_route *route);

t_graph_node *pf_tGraphNodeInit(int id);

t_graph_node *
pf_findNodeByName(t_graph_core *graph, char *name, bool createIfNotFound);

t_graph_node *pf_findNodeByID(t_graph_core *graph, int id);

bool pf_addRoadToNode(t_graph_node *node1, t_graph_node *node2, int dist);
//dist має бути завжди позитивним,
//інакше шлях буде лише в node1 з позитивним значенням

t_graph_node *pf_minIDInRoadsNotInf (t_graph_node *node);

void pf_freeNode (t_graph_node *node);

void pf_freeGraph (t_graph_core *graph);

int pf_checkOverflow(int num1, int num2);

/*pathfinder_core.c*/

void pf_shortWaysCore(t_graph_core *graph);

void pf_sWCAlgorithm(t_graph_node *start);

void pf_sWCreload(t_graph_core *graph);

t_graph_node *pf_sWCMinNotStopped (t_graph_node *node);

void pf_sWCaddPath(t_graph_node *node, int target);

/*pathfinder_print.c*/

void pf_printNodeRoutes(t_graph_core *graph, t_graph_node *startNode,
                        t_graph_node *node);

void pf_printNodeRoutesByID(t_graph_core *graph, t_graph_node *startNode);

void pf_errorPrinter(t_graph_core *graph, char *filename);

int pf_pathcmpID(int *A, int *B);

void pf_sortPathsByID(t_graph_node *node);

#endif
