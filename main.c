#include "graph.h"
#include "dialog.h"

int main() {
    Graph g = {0};
    const char *msgs[ ] = {"0. Quit", "1. Add node","2. Add edge", "3. Delete node", "4. Delete edge","5. Show","6. Bfs","7. Min Search","8. Graphviz"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[ ])(Graph *) = {NULL, Add_node, Add_edge,Del_node, Del_edge, Show,Bfs,MinSearch,Graphviz };
    int rc;
    rc = dialog(msgs, NMsgs);
    while(rc){
        if(!fptr[rc](&g)){
            break;
        }
        rc = dialog(msgs, NMsgs);
    }
    freeG(&g);
    printf("That's all. Bye!\n");
    return 0;
}
