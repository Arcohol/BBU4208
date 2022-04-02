/* Topological Sorting */

#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 11

typedef char Vertex;
typedef int Graph[NUM_VERTEX][NUM_VERTEX];

typedef int NodeVal;
typedef struct Node {
    NodeVal val;
    struct Node *prev, *next;
} Node;
typedef struct Collection {
    Node *head, *tail;
} Collection;
typedef Collection *Queue;

Queue CreateQueue();
int IsEmpty(Queue Q);
void Enque(NodeVal val, Queue Q);
NodeVal Deque(Queue Q);
void DisposeQueue(Queue Q);

void ReadGraph(Graph G);
void TopSort(Graph G);
int Hash(char X);

char _GRAPH[] =
    "A B, A E, B C, C T, D E, D A, E C, E F, E I, F C, F T, G D, G E, G H, H E, H I, I F, I T, S "
    "A, S D, S G, ";
int _INDEGREE[NUM_VERTEX];
Vertex _MAP[NUM_VERTEX] = {'S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'T'};

int main() {
    Graph G = {0};
    Vertex A, B;

    ReadGraph(G);

    scanf("%c,%c", &A, &B);
    G[Hash(A)][Hash(B)] = 0;
    _INDEGREE[Hash(B)]--;

    TopSort(G);

    return 0;
}

void ReadGraph(Graph G) {
    Vertex A, B;
    char *s = _GRAPH;
    int offset;

    while (sscanf(s, "%c %c, %n", &A, &B, &offset) != EOF) {
        s += offset;
        G[Hash(A)][Hash(B)] = 1;
        _INDEGREE[Hash(B)]++;
    }
}

void TopSort(Graph G) {
    Queue Q;
    NodeVal del;

    Q = CreateQueue();

    for (int i = 0; i < NUM_VERTEX; i++) {
        if (_INDEGREE[i] == 0) {
            Enque(i, Q);
        }
    }

    while (!IsEmpty(Q)) {
        del = Deque(Q);
        printf("%c,", _MAP[del]);
        for (int i = 0; i < NUM_VERTEX; i++) {
            if (G[del][i]) {
                if (--_INDEGREE[i] == 0) {
                    Enque(i, Q);
                }
            }
        }
    }

    DisposeQueue(Q);
}

int Hash(char X) {
    int R;

    if (X == 'S') {
        R = 0;
    } else if (X == 'T') {
        R = 10;
    } else {
        R = X - 'A' + 1;
    }

    return R;
}

Queue CreateQueue() {
    Queue Q;

    Q = (Queue)malloc(sizeof(Collection));
    Q->head = Q->tail = NULL;

    return Q;
}

int IsEmpty(Queue Q) { return Q->head == NULL; }

void Enque(NodeVal val, Queue Q) {
    Node *new;

    new = (Node *)malloc(sizeof(Node));

    new->val = val;
    new->prev = NULL;
    new->next = Q->head;

    if (Q->head == NULL) {
        Q->head = Q->tail = new;
    } else {
        Q->head->prev = new;
        Q->head = new;
    }
}

NodeVal Deque(Queue Q) {
    Node *del;
    NodeVal val;

    del = Q->tail;
    val = del->val;
    Q->tail = del->prev;

    if (Q->tail == NULL) {
        Q->head = NULL;
    } else {
        Q->tail->next = NULL;
    }

    free(del);

    return val;
}

void DisposeQueue(Queue Q) {
    while (!IsEmpty(Q)) {
        Deque(Q);
    }
    free(Q);
}