/* There are N people, numbered from 1 to N, sitting around in a circle. Counted from the NO.1, the
 * M th people should leave the game. Then, from the next one, the counting loop will go on. After
 * several loops, there will be only on guy left. Writing a program to calculate who is the last
 * people. */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node {
    ElementType val;
    struct Node *next;
} Node;

Node *CreateNode(ElementType X);

int main() {
    Node *head = NULL, *new, *prev, *curr;
    int count, pass;

    scanf("%d,%d", &count, &pass);

    for (int i = 1; i <= count; i++) {
        new = CreateNode(i);

        if (head == NULL) {
            head = new;
        } else {
            curr->next = new;
        }

        curr = new;
    }
    curr->next = head;

    curr = head;
    while (curr->next != curr) {
        for (int i = 0; i < pass; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;

        printf("%d,", curr->val);
        free(curr);

        curr = prev->next;
    }
    printf("%d", curr->val);
    free(curr);

    return 0;
}

Node *CreateNode(ElementType X) {
    Node *new_node;

    new_node = (Node *)malloc(sizeof(Node));
    new_node->val = X;
    new_node->next = NULL;

    return new_node;
}