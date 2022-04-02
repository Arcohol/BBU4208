/* Modify an edge of the following graph, and then give the Minmum Spanning Tree. */

#include <stdbool.h>
#include <stdio.h>

#define NOT_A_VERTEX -1
#define NUM_VERTEX 10
#define INFINITY 0x3f3f3f3f

typedef char Vertex;
typedef int Graph[NUM_VERTEX][NUM_VERTEX];
typedef struct TableEntry {
    Vertex V;
    bool known;
    int dist;
    Vertex path;
} TableEntry;
typedef TableEntry Table[NUM_VERTEX];

int Hash(Vertex V);
void ReadGraph(Graph G);
void InitTable(Vertex V, Graph G, Table T);
void Prim(Graph G, Table T);
void InsertionSort(int A[], int N);

char _GRAPH[] =
    "A B 3, B C 10, A D 4, A E 4, B E 2, B F 3, C F 6, C G 1, D E 5, E F 11, F G 2, D H 6, E H 2, "
    "E I 1, F I 3, F J 11, G J 8, H I 4, I J 7, ";
Vertex _MAP[NUM_VERTEX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

int main() {
    Graph G = {0};
    Table T = {0};
    Vertex A, B;
    int dist, output[NUM_VERTEX] = {0};

    ReadGraph(G);
    InitTable('A', G, T);

    scanf("%c,%c,%d", &A, &B, &dist);
    G[Hash(A)][Hash(B)] = G[Hash(B)][Hash(A)] = dist;

    Prim(G, T);

    for (int i = 0; i < NUM_VERTEX; i++) {
        output[i] = T[i].dist;
    }
    InsertionSort(output, NUM_VERTEX);
    for (int i = 0; i < NUM_VERTEX; i++) {
        if (output[i]) {
            printf("%d,", output[i]);
        }
    }

    return 0;
}

int Hash(Vertex V) {
    int R;

    R = V - 'A';

    return R;
}

void ReadGraph(Graph G) {
    Vertex A, B;
    char *s = _GRAPH;
    int dist, offset;

    while (sscanf(s, "%c %c %d, %n", &A, &B, &dist, &offset) != EOF) {
        s += offset;
        G[Hash(A)][Hash(B)] = G[Hash(B)][Hash(A)] = dist;
    }
}

void InitTable(Vertex V, Graph G, Table T) {
    for (int i = 0; i < NUM_VERTEX; i++) {
        T[i].V = _MAP[i];
        T[i].known = false;
        T[i].dist = INFINITY;
        T[i].path = NOT_A_VERTEX;
    }
    T[Hash(V)].dist = 0;
}

void Prim(Graph G, Table T) {
    int V;
    int min_dist;

    for (;;) {
        V = NOT_A_VERTEX;
        for (int i = 0; i < NUM_VERTEX; i++) {
            if (!T[i].known && (V == NOT_A_VERTEX || T[i].dist < min_dist)) {
                V = i;
                min_dist = T[i].dist;
            }
        }
        if (V == NOT_A_VERTEX) {
            break;
        }

        T[V].known = true;
        for (int i = 0; i < NUM_VERTEX; i++) {
            if (G[V][i] && !T[i].known && G[V][i] < T[i].dist) {
                T[i].dist = G[V][i];
                T[i].path = V;
            }
        }
    }
}

void InsertionSort(int A[], int N) {
    int tmp, i, j;

    for (i = 1; i < N; i++) {
        tmp = A[i];
        for (j = i; j > 0 && A[j - 1] > tmp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = tmp;
    }
}