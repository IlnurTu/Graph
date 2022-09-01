#include "graph.h"

int add_node(Graph* g, char* key){
    for (int i = 0; i < g->count; i++) {
        if (strcmp(g->list[i]->key, key) == 0) {
            return 0;
        }
    }
    g->count++;
    g->list =(node**) realloc(g->list,sizeof(node*)*g->count);
    node* tmp = (node*)calloc(1,sizeof(node));
    tmp->key = strdup(key);
    g->list[g->count-1] = tmp;
    return 1;
}

int search_index(Graph* g, char* key){
    for(int i =0;i<g->count;i++){
        if(strcmp(g->list[i]->key,key)==0){
            return i;
        }
    }
    return -1;
}

int add_edge(Graph* g,char* from,char* to,int weight){
    int x = search_index(g,from);
    int y = search_index(g,to);
    if(x == -1 || y==-1){
        return 0;
    }
    node* tmp = g->list[x]->next;
    while(tmp){
        if (strcmp(tmp->key,to)==0){
            tmp->weight = weight;
            return 1;
        }
        tmp = tmp->next;
    }
    tmp = (node*) calloc(1,sizeof(node));
    tmp->key = strdup(to);
    tmp->weight = weight;
    tmp->next = g->list[x]->next;
    g->list[x]->next = tmp;
    return 1;
}

int del_node(Graph* g,char* key){
    int index = search_index(g,key);
    if(index==-1) return 0;
    node* tmp = g->list[index];
    node* next;
    while(tmp){
        next = tmp->next;
        free(tmp->key);
        free(tmp);
        tmp = next;
    }
    g->count--;
    for(int i = index;i<g->count;i++){
        g->list[i] = g->list[i+1];
    }
    g->list = (node**)realloc(g->list,g->count*sizeof(node));
    for(int i = 0;i<g->count;i++){
        node*tmp = g->list[i]->next;
        node* par = g->list[i];
        while(tmp){
            if(strcmp(tmp->key,key)==0){
                par->next = tmp->next;
                free(tmp->key);
                free(tmp);
                break;
            }
            par = tmp;
            tmp = tmp->next;
        }
    }
    return 1;
}

int del_edge(Graph* g,char* from,char*to ){
    int index = search_index(g,from);
    int x = search_index(g,to);
    if(index == -1 || x == -1) return 0;
    node* par = g->list[index];
    node* tmp = par->next;
    while(tmp){
        if(strcmp(tmp->key,to)==0){
            par->next = tmp->next;
            free(tmp->key);
            free(tmp);
        }
        par = tmp;
        tmp = tmp->next;
    }
    return 1;
}

void show(Graph* g){
    for (int i =0;i<g->count;i++){
        node* tmp = g->list[i];
        while(tmp){
            printf("%s",tmp->key);
            tmp = tmp->next;
            if(tmp){
                printf("-%d->",tmp->weight);
            }
            else{
                printf("\n");
            }
        }
    }
}

void push(queue* pq,el* pe){
    if(pq->head==NULL){
        pq->head = pe;
    }
    else pq->tail->next = pe;
    pq->tail = pe;
}

void pop(queue* pq,el** pe){
    if (pq->head==NULL){
        pe = NULL;
        return;
    }
    *pe = pq->head;
    pq->head = (*pe)->next;
    if(pq->head==NULL) pq->tail=NULL;
}

void searchWide(Graph* g,char*from,char*to){
//white - 0; grey - 1; black - 2;
    int x = search_index(g, from);
    int y = search_index(g,to);
    if(x==-1 ||  y==-1) {
        printf("Error!\n");
        return ;
    }
    
    queue* pq = (queue*)calloc(1,sizeof(queue));
    el* init = (el*)calloc(g->count,sizeof(el));
    for(int i = 0;i<g->count;i++){
        init[i].key = g->list[i]->key;
        init[i].d = inf;
    }
    init[x].color=1;
    init[x].d = 0;
    push(pq,&init[x]);
    
    el* tmp = NULL;
    while(pq->head!=NULL){
        pop(pq,&tmp);
        int u = search_index(g, tmp->key);
        node* el = g->list[u]->next;
        while(el){
            int v = search_index(g, el->key);
            if(init[v].color == 0){
                init[v].color = 1;
                init[v].d = init[u].d + el->weight;
                init[v].pred = u;
                push(pq,&init[v]);
            }
            el = el->next;
        }
        init[u].color = 2;
    }
    
    if(init[y].d==inf){
        printf("Error!\n");
    }
    else{
        int maxlen = 10;
        char** keys = calloc(maxlen,sizeof(char*));
        int len = 0;
        while(x!=y){
            len++;
            if(len>maxlen-1){
                maxlen = maxlen*2;
                keys = realloc(keys,maxlen*sizeof(char*));
            }
            keys[len-1] = init[y].key;
            y = init[y].pred;
        }
        len++;
        keys[len-1] =init[x].key;
        for(int i = len;i!=0;i--){
            printf("%s",keys[i-1]);
            if(i!=1){
                printf("-->");
            }
        }
        printf("\n");
        free(keys);
        free(init);
        free(pq);
    }
}

void freeG(Graph*g){
    for(int i = 0;i<g->count;i++){
        node* tmp = g->list[i];
        node* next;
        while(tmp){
            next = tmp->next;
            free(tmp->key);
            free(tmp);
            tmp = next;
        }
    }
}

void minsearch(Graph* g,char* from,char* to){
    int x = search_index(g, from);
    int y = search_index(g,to);
    if(x==-1 ||  y==-1) {
        printf("Error!\n");
        return ;
    }
    
    elem* init = (elem*)calloc(g->count,sizeof(elem));
    for(int i = 0;i<g->count;i++){
        init[i].key = g->list[i]->key;
        init[i].d = inf;
    }
    init[x].d = 0;
    
    for(int i = 0;i<g->count-1;i++){
        for(int j = 0 ;j<g->count;j++){
            node* tmp = g->list[j]->next;
            while(tmp){
                int index = search_index(g, tmp->key);
                if(init[j].d != inf &&(init[index].d==inf || init[index].d>(init[j].d+tmp->weight))){
                    init[index].d = init[j].d+tmp->weight;
                    init[index].pred = j;
                }
                tmp =tmp ->next;
            }
        }
    }
    
    if(init[y].d==inf){
        printf("Error!\n");
    }
    else{
        printf("d = %d\n",init[y].d);
        int maxlen = 10;
        char** keys = calloc(maxlen,sizeof(char*));
        int len = 0;
        while(x!=y){
            len++;
            if(len>maxlen-1){
                maxlen = maxlen*2;
                keys = realloc(keys,maxlen*sizeof(char*));
            }
            keys[len-1] = init[y].key;
            y = init[y].pred;
        }
        len++;
        keys[len-1] =init[x].key;
        for(int i = len;i!=0;i--){
            printf("%s",keys[i-1]);
            if(i!=1){
                printf("-->");
            }
        }
        printf("\n");
        free(keys);
        free(init);
    }
}

void graphviz(Graph* g){
    FILE* pf = fopen("Graph","w");
    fprintf(pf,"digraph G {\n");
    for(int i = 0; i<g->count;i++){
        node* tmp = g->list[i]->next;
        if(!tmp) fprintf(pf, "%s\n",g->list[i]->key);
        while(tmp){
            fprintf(pf, "%s -> %s [label = %d]\n",g->list[i]->key,tmp->key,tmp->weight);
            tmp = tmp->next;
        }
    }
    fprintf(pf, "}");
    fclose(pf);
    system("dot -Tpng Graph -o Graph.png");
    system("open Graph.png");
    
}

