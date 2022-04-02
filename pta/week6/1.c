/* 模拟微信朋友圈点赞的场景，要求用十字链表的方式进行数据结构的设计。
 * 共有5个人，序号分别是0到4.他们之间有不同的关注关系，这个关系由输入的序列来决定。
 * 每个人都发表了一个朋友圈的短语，关注他的人进行点赞或不点赞，点赞的规则为
 * 每个人对其关注的朋友按照序号进行排序，只对其关注的朋友中的顺序为奇数的朋友点赞，对偶数的朋友不点赞。要求计算某个人被点赞的情况。
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 5

typedef int Vertex;
typedef struct ArcNode {
    int is_liked;
    Vertex tail, head;
    struct ArcNode *tail_link, *head_link;
} ArcNode;
typedef struct VexNode {
    ArcNode *first_in, *first_out;
} VexNode;
typedef VexNode Graph[NUM_VERTEX];

void ReadGraph(Graph G);
void DisposeGraph(Graph G);

int main() {
    Graph G = {0};
    ArcNode *scan;
    Vertex V;
    int count = 0;

    ReadGraph(G);

    for (int i = 0; i < NUM_VERTEX; i++) {
        scan = G[i].first_out;
        for (int i = 1; scan != NULL; scan = scan->tail_link, i++) {
            if (i % 2) {
                scan->is_liked = 1;
            }
        }
    }

    scanf("%d", &V);

    scan = G[V].first_in;
    while (scan != NULL) {
        if (scan->is_liked) {
            printf("%d,", scan->tail);
            count++;
        }
        scan = scan->head_link;
    }

    if (!count) {
        printf("-1");
    }

    DisposeGraph(G);

    return 0;
}

void ReadGraph(Graph G) {
    Vertex tail, head;
    ArcNode *new, *scan;
    char str[100], *s = str;
    int offset;

    scanf("%s", str);

    while (sscanf(s, "%d,%d,%n", &tail, &head, &offset) != EOF) {
        s += offset;

        new = (ArcNode *)malloc(sizeof(ArcNode));
        new->is_liked = 0;
        new->tail = tail;
        new->head = head;
        new->tail_link = new->head_link = NULL;

        if (G[tail].first_out == NULL) {
            G[tail].first_out = new;
        } else if (head < G[tail].first_out->head) {
            new->tail_link = G[tail].first_out;
            G[tail].first_out = new;
        } else {
            scan = G[tail].first_out;
            while (scan->tail_link != NULL && scan->tail_link->head < head) {
                scan = scan->tail_link;
            }
            new->tail_link = scan->tail_link;
            scan->tail_link = new;
        }

        if (G[head].first_in == NULL) {
            G[head].first_in = new;
        } else if (tail < G[head].first_in->tail) {
            new->head_link = G[head].first_in;
            G[head].first_in = new;
        } else {
            scan = G[head].first_in;
            while (scan->head_link != NULL && scan->head_link->tail < tail) {
                scan = scan->head_link;
            }
            new->head_link = scan->head_link;
            scan->head_link = new;
        }
    }
}

void DisposeGraph(Graph G) {
    ArcNode *scan, *del;

    for (int i = 0; i < NUM_VERTEX; i++) {
        scan = G[i].first_out;
        while (scan != NULL) {
            del = scan;
            scan = scan->tail_link;
            free(del);
        }
    }
}