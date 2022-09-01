//
//  dialog.c
//  lab5
//
//  Created by Ильнур Тухватулин on 26.05.2022.
//

#include "dialog.h"
#include "graph.h"

int getInt(int* a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            printf("Error! Repeat again:\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
        if (n < 0) {
            return 0;
        }
    } while (n == 0);
    scanf("%*[^\n]");
    scanf("%*c");
    return 1;
}

int dialog(const char* msgs[], int N) {
    const char* errmsgs = "";
    int rc;
    int i, n;
    do {
        puts(errmsgs);
        errmsgs = "You are wrong! Repeate, please";
        for (i = 0; i < N; i++) {
            puts(msgs[i]);
        }
        puts("Make your choice: -->");
        n = getInt(&rc);
        if (n == 0) {
            rc = 0;
        }
    } while (rc < 0 || rc > N);
    return rc;
}

char* getStr(void)
{
    char* result = NULL;
    char buf[1000] = {0};
    int n;
    int len = 0;
    int newLen, tmp;
    do {
        n = scanf("%999[^\n]", buf);
        if (n < 0) {
            if (!result) return NULL;
        }
        else if (n > 0) {
            tmp = (int)strlen(buf);
            newLen = tmp + len;
            result = (char*)realloc(result, newLen + 1);
            memcpy(result + len, buf, tmp);
            len = newLen;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len == 0) {
        result = (char*)calloc(1, sizeof(char));
    }
    else {
        result[len] = '\0';
    }
    return result;
}


int Add_node(Graph* g){
    printf("Enter key of new node:--> ");
    char* key = getStr();
    if(!key) return 0;
    int flag = add_node(g,key);
    if(!flag){
        printf("Node with this key has already existed\n");
    }
    free(key);
    return 1;
}

int Add_edge(Graph* g){
    printf("Enter key from and to:-->\n");
    char* from = getStr();
    if(!from) return 0;
    char* to = getStr();
    if(!to) {
        free(from);
        return 0;
    }
    printf("Enter weight of edge:-->");
    int weight = 0;
    int n = getInt(&weight);
    if(!n){
        free(from);
        free(to);
        return 0;
    }
    n = add_edge(g,from,to,weight);
    if(!n){
        printf("There are not such nodes\n");
    }
    return 1;
}

int Del_node(Graph* g){
    printf("Enter key:--> ");
    char* key = getStr();
    if(!key) return 0;
    int n = del_node(g,key);
    if(!n){
        printf("There is no such node\n");
    }
    free(key);
    return 1;
}

int Del_edge(Graph* g){
    printf("Enter key from and to:-->\n");
    char* from = getStr();
    if(!from) return 0;
    char* to = getStr();
    if(!to) {
        free(from);
        return 0;
    }
    int n = del_edge(g,from,to);
    if(!n){
        printf("There are no such nodes\n");
    }
    free(from);
    free(to);
    return 1;
}

int Show(Graph*g){
    show(g);
    return 1;
}

int Bfs(Graph* g){
    printf("Enter key from and to:-->\n");
    char* from = getStr();
    if(!from) return 0;
    char* to = getStr();
    if(!to) {
        free(from);
        return 0;
    }
    searchWide(g, from, to);
    free(from);
    free(to);
    return 1;
}

int MinSearch(Graph* g){
    printf("Enter key from and to:-->\n");
    char* from = getStr();
    if(!from) return 0;
    char* to = getStr();
    if(!to) {
        free(from);
        return 0;
    }
    minsearch(g, from, to);
    free(from);
    free(to);
    return 1;
}

int Graphviz(Graph* g){
    graphviz(g);
    return 1;
}
