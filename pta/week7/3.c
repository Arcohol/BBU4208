#include <stdio.h>

#define NUM_VERTEX 7
#define INFINITY 0x3f3f3f3f

typedef int Vertex;
typedef struct TableEntry {
    int EC, LC;
} TableEntry;
typedef TableEntry Table[NUM_VERTEX + 1];
typedef int Graph[NUM_VERTEX + 1][NUM_VERTEX + 1];

void ReadGraph(Graph G);
void ComputeEC(Graph G, Table T);
void ComputeLC(Graph G, Table T);

char _GRAPH[] =
    "1 2 3, 1 4 6, 1 3 3, 2 4 2, 3 4 3, 2 5 5, 4 5 2, 3 6 3, 4 6 2, 4 7 5, 5 7 3, 6 7 4, ";

int main() {
    Graph G = {0};
    Table T = {0};
    Vertex A, B, C;

    ReadGraph(G);

    scanf("%d,%d,%d,", &A, &B, &C);
    G[A][B] = 0;

    ComputeEC(G, T);
    ComputeLC(G, T);

    printf("%d", T[C].LC - T[C].EC);

    return 0;
}

void ReadGraph(Graph G) {
    Vertex A, B;
    char *s = _GRAPH;
    int dist, offset;

    while (sscanf(s, "%d %d %d, %n", &A, &B, &dist, &offset) != EOF) {
        s += offset;
        G[A][B] = dist;
    }
}

void ComputeEC(Graph G, Table T) {
    int max;

    T[1].EC = 0;
    for (Vertex W = 2; W <= NUM_VERTEX; W++) {
        max = -1;
        for (Vertex V = 1; V <= NUM_VERTEX; V++) {
            if (G[V][W] && T[V].EC + G[V][W] > max) {
                max = T[V].EC + G[V][W];
            }
        }
        T[W].EC = max;
    }
}

void ComputeLC(Graph G, Table T) {
    int min;

    T[NUM_VERTEX].LC = T[NUM_VERTEX].EC;
    for (Vertex V = NUM_VERTEX - 1; V >= 1; V--) {
        min = INFINITY;
        for (Vertex W = 1; W <= NUM_VERTEX; W++) {
            if (G[V][W] && T[W].LC - G[V][W] < min) {
                min = T[W].LC - G[V][W];
            }
        }
        T[V].LC = min;
    }
}