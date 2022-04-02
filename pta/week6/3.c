/* Shortest Path */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NOT_A_VERTEX -1
#define NUM_VERTEX 7
#define INFINITY 0x3f3f3f3f

typedef int Vertex;
typedef struct VexNode {
    Vertex val;
    int dist;
    struct VexNode *next;
} VexNode;
typedef VexNode *VexList;
typedef VexList Graph[NUM_VERTEX + 1];

typedef struct TableEntry {
    VexList header;
    bool known;
    int dist;
    Vertex path;
} TableEntry;
typedef TableEntry Table[NUM_VERTEX + 1];

void ReadGraph(Graph G);
void InitTable(Vertex V, Table T, Graph G);
void Dijkstra(Table T);
void PrintPath(Vertex V, Table T);
void DisposeGraph(Graph G);

char _GRAPH[] =
    "1 2 2, 1 4 1, 2 4 3, 2 5 10, 3 1 4, 3 6 5, 4 3 2, 4 5 2, 4 6 8, 4 7 4, 5 7 6, 7 6 1, ";

int main() {
    Graph G = {0};
    Table T = {0};
    Vertex V, W;

    scanf("%d,%d", &V, &W);

    ReadGraph(G);
    InitTable(V, T, G);

    Dijkstra(T);

    if (T[W].path == NOT_A_VERTEX) {
        printf("-1");
    } else {
        PrintPath(W, T);
    }

    DisposeGraph(G);

    return 0;
}

void ReadGraph(Graph G) {
    VexList new_list;
    VexNode *new_node;
    Vertex V, W;
    char *s = _GRAPH;
    int dist, offset;

    for (int i = 1; i <= NUM_VERTEX; i++) {
        new_list = (VexList)malloc(sizeof(VexNode));
        new_list->val = i;
        new_list->dist = 0;
        new_list->next = NULL;

        G[i] = new_list;
    }

    while (sscanf(s, "%d %d %d, %n", &V, &W, &dist, &offset) != EOF) {
        s += offset;

        new_node = (VexNode *)malloc(sizeof(VexNode));
        new_node->val = W;
        new_node->dist = dist;
        new_node->next = G[V]->next;
        G[V]->next = new_node;
    }
}

void InitTable(Vertex V, Table T, Graph G) {
    for (int i = 1; i <= NUM_VERTEX; i++) {
        T[i].header = G[i];
        T[i].known = false;
        T[i].dist = INFINITY;
        T[i].path = NOT_A_VERTEX;
    }
    T[V].dist = 0;
}

void Dijkstra(Table T) {
    int V, W;
    VexNode *scan;
    int min_dist;

    for (;;) {
        V = NOT_A_VERTEX;
        for (int i = 1; i <= NUM_VERTEX; i++) {
            if (!T[i].known && (V == NOT_A_VERTEX || T[i].dist < min_dist)) {
                V = i;
                min_dist = T[i].dist;
            }
        }
        if (V == NOT_A_VERTEX) {
            break;
        }

        T[V].known = true;

        scan = T[V].header->next;
        while (scan != NULL) {
            W = scan->val;
            if (!T[W].known && T[V].dist + scan->dist < T[W].dist) {
                T[W].dist = T[V].dist + scan->dist;
                T[W].path = V;
            }
            scan = scan->next;
        }
    }
}

void PrintPath(Vertex V, Table T) {
    if (T[V].path != NOT_A_VERTEX) {
        PrintPath(T[V].path, T);
    }
    printf("%d,", V);
}

void DisposeGraph(Graph G) {
    VexNode *scan, *del;

    for (int i = 1; i <= NUM_VERTEX; i++) {
        scan = G[i];
        while (scan != NULL) {
            del = scan;
            scan = scan->next;
            free(del);
        }
    }
}