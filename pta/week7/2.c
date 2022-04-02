#include <stdio.h>

#define NUM_VERTEX 8

typedef int Vertex;
typedef int Graph[NUM_VERTEX + 1][NUM_VERTEX + 1];

void ReadGraph(Graph G);
void DFS(Vertex V, Graph G);

char _GRAPH[] = "1 2, 1 3, 2 4, 2 5, 3 6, 3 7, 4 8, 5 8, 6 8, 7 8, ";
int _VISITED[NUM_VERTEX + 1];

int main() {
    Graph G = {0};
    Vertex V;

    scanf("%d", &V);

    ReadGraph(G);

    DFS(V, G);

    return 0;
}

void ReadGraph(Graph G) {
    Vertex A, B;
    char *s = _GRAPH;
    int offset;

    while (sscanf(s, "%d %d, %n", &A, &B, &offset) != EOF) {
        s += offset;
        G[A][B] = G[B][A] = 1;
    }
}

void DFS(Vertex V, Graph G) {
    printf("%d,", V);
    _VISITED[V] = 1;
    for (Vertex W = 1; W <= NUM_VERTEX; W++) {
        if (G[V][W] && !_VISITED[W]) {
            DFS(W, G);
        }
    }
}