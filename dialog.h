#pragma once
#include "graph.h"

int getInt(int* a) ;

int dialog(const char* msgs[], int N) ;

char* getStr(void);

int Add_node(Graph* g);

int Add_edge(Graph* g);

int Del_node(Graph* g);

int Del_edge(Graph* g);

int Show(Graph* g);

int Bfs(Graph* g);

int MinSearch(Graph* g);
int Graphviz(Graph* g);
