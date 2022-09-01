#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define inf INT_MAX

typedef struct node{
    char* key;
    struct node* next;
    int weight;
}node;

typedef struct Graph{
    node** list;
    int count;
}Graph;

typedef struct el{
    int color;
    char* key;
    int d;
    int pred;
    struct el* next;
    
}el;

typedef struct queue{
    el* head;
    el* tail;
}queue;

typedef struct elem{
    char* key;
    int d;
    int pred;
}elem;

int add_node(Graph* g, char* key);

int search_index(Graph* g, char* key);

int add_edge(Graph* g,char* from,char* to,int weight);

int del_node(Graph* g,char* key);

int del_edge(Graph* g,char* from,char*to );

void show(Graph* g);

void push(queue* pq,el* pe);

void pop(queue* pq,el** pe);

void searchWide(Graph* g,char*from,char*to);

void freeG(Graph*g);

void minsearch(Graph*g,char* from,char* to);

void graphviz(Graph* g);
