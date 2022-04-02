#include <stdio.h>

#define NUM_VERTEX 1000

typedef int Vertex;
typedef int Graph[NUM_VERTEX + 1][NUM_VERTEX + 1];

void ReadGraph(Graph G);
void DFS(Vertex V, Graph G);
int IsConnected(Graph G);
int IsCircuit(Graph G);

int _DEGREE[NUM_VERTEX + 1], _VISITED[NUM_VERTEX + 1], _NUM_VERTEX, _NUM_EDGE, _IS_CIRCUIT = 1;

int main() {
    Graph G;

    scanf("%d%d", &_NUM_VERTEX, &_NUM_EDGE);

    ReadGraph(G);

    printf("%d", IsCircuit(G));

    return 0;
}

void ReadGraph(Graph G) {
    Vertex A, B;

    for (int i = 0; i < _NUM_EDGE; i++) {
        scanf("%d%d", &A, &B);
        G[A][B] = G[B][A] = 1;
        _DEGREE[A]++;
        _DEGREE[B]++;
    }
}

void DFS(Vertex V, Graph G) {
    _VISITED[V] = 1;
    for (Vertex W = 1; W <= _NUM_VERTEX; W++) {
        if (G[V][W] && !_VISITED[W]) {
            DFS(W, G);
        }
    }
}

int IsConnected(Graph G) {
    DFS(1, G);

    for (Vertex V = 1; V <= _NUM_VERTEX; V++) {
        if (!_VISITED[V]) {
            return 0;
        }
    }

    return 1;
}

int IsCircuit(Graph G) {
    if (!IsConnected(G)) {
        return 0;
    }

    for (Vertex V = 1; V <= _NUM_VERTEX; V++) {
        if (_DEGREE[V] % 2) {
            return 0;
        }
    }

    return 1;
}