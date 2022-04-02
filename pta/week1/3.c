/* If a list is central symmetry, it is called a central list. for example,
 * 1->3->5->7->9->7->5->3->1 is a central list. Give you a sequence of numbers, form a link list and
 * then judge whether it is a central list. */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node {
    ElementType val;
    struct Node *next, *prev;
} Node;
typedef Node *List;

Node *CreateNode(ElementType X);
void DisposeList(List L);

int main() {
    Node *head = NULL, *tail = NULL, *curr, *new;
    int X, count = 0, error = 0;

    while (scanf("%d,", &X) != EOF) {
        count++;
        new = CreateNode(X);
        if (head == NULL) {
            head = new;
        } else {
            curr->next = new;
            new->prev = curr;
        }
        curr = new;
    }
    tail = curr;

    curr = head;

    count /= 2;
    for (int i = 0; i < count; i++) {
        if (head->val != tail->val) {
            error = 1;
            break;
        }
        head = head->next;
        tail = tail->prev;
    }

    if (!error) {
        printf("Yes");
    } else {
        printf("No");
    }

    DisposeList(curr);

    return 0;
}

Node *CreateNode(ElementType X) {
    Node *new_node;

    new_node = (Node *)malloc(sizeof(Node));
    new_node->val = X;
    new_node->next = new_node->prev = NULL;

    return new_node;
}

void DisposeList(List L) {
    Node *del, *scan;

    scan = L;
    while (scan != NULL) {
        del = scan;
        scan = scan->next;
        free(del);
    }
}