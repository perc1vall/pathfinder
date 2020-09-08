#include "pathfinder.h"
#include "libmx.h"

//TODO check all errors texts etc.

int main(int argc, char **argv) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]");
        return 0;
    }
    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        mx_printerr("error: file does not exist");
        return 0;
    }
    t_graph_core *graph = pf_tGraphCoreInit(file);
    pf_readFileData(&graph);
    if (graph->err_flag)
        pf_errorPrinter(graph, argv[1]);
    else
        pf_shortWaysCore(graph);
    pf_freeGraph(graph);
    return 0;
}
