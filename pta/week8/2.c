#include <stdio.h>

#define NUM_VERTEX 200

typedef int Vertex;
typedef int Graph[NUM_VERTEX + 1][NUM_VERTEX + 1];

void ReadGraph(Graph G);
int CheckPath(Graph G);

int _DEGREE[NUM_VERTEX + 1], _NUM_VERTEX, _NUM_EDGE;

int main() {
    Graph G;
    int K;

    scanf("%d%d", &_NUM_VERTEX, &_NUM_EDGE);

    ReadGraph(G);

    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        if (CheckPath(G)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

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

int CheckPath(Graph G) {
    Vertex A, B;
    int N, count[_NUM_VERTEX + 1];

    for (int i = 1; i <= _NUM_VERTEX; i++) {
        count[i] = 0;
    }

    scanf("%d", &N);

    scanf("%d", &A);
    for (int i = 0; i < N - 1; i++) {
        scanf("%d", &B);
        if (G[A][B]) {
            count[B]++;
            A = B;
        }
    }

    if (N - 1 != _NUM_VERTEX) {
        return 0;
    }

    for (int i = 1; i <= _NUM_VERTEX; i++) {
        if (count[i] != 1) {
            return 0;
        }
    }

    return 1;
}