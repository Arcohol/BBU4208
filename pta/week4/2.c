/* Give a sequence of numbers(>0), build a Binomial Queue by inserting them one by one. At last
 * output the k-th binomial tree (a multi-branches tree) by level order. If the k-th tree is null,
 * output 0. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef int ElementType;

typedef struct BinNode {
    ElementType val;
    struct BinNode *first_child, *next_sibling;
} BinNode;
typedef BinNode *BinTree;

typedef struct Collection {
    int size;
    BinTree trees[MAX_SIZE];
} Collection;
typedef Collection *BinQueue;

BinQueue InitBinQueue();
BinTree CombineTrees(BinTree T1, BinTree T2);
BinQueue Merge(BinQueue H1, BinQueue H2);
BinQueue Insert(BinQueue H, ElementType X);
void PrintTree(BinTree T, int number);
void LevelOrderTraversal(BinTree T, int level);
void DisposeBinQueue(BinQueue H);
void DisposeBinTree(BinTree T);

ElementType F[MAX_SIZE][MAX_SIZE];

int main() {
    BinQueue H;
    char str[100], *s = str;
    int X, offset, target;

    scanf("%s%d", str, &target);

    H = InitBinQueue();

    while (sscanf(s, "%d,%n", &X, &offset) != EOF) {
        s += offset;
        H = Insert(H, X);
    }

    if (H->trees[target] == NULL) {
        printf("0,");
    } else {
        PrintTree(H->trees[target], target);
    }

    DisposeBinQueue(H);

    return 0;
}

BinQueue InitBinQueue() {
    BinQueue H;

    H = (BinQueue)malloc(sizeof(Collection));
    H->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        H->trees[i] = NULL;
    }

    return H;
}

BinTree CombineTrees(BinTree T1, BinTree T2) {
    if (T1->val > T2->val) {
        return CombineTrees(T2, T1);
    }

    T2->next_sibling = T1->first_child;
    T1->first_child = T2;

    return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2) {
    BinTree T1, T2, carry = NULL;

    H1->size += H2->size;
    for (int i = 0, j = 1; j <= H1->size; i++, j *= 2) {
        T1 = H1->trees[i];
        T2 = H2->trees[i];

        switch (!!T1 + 2 * !!T2 + 4 * !!carry) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                H1->trees[i] = T2;
                H2->trees[i] = NULL;
                break;
            case 3:
                carry = CombineTrees(T1, T2);
                H1->trees[i] = H2->trees[i] = NULL;
                break;
            case 4:
                H1->trees[i] = carry;
                carry = NULL;
                break;
            case 5:
                carry = CombineTrees(T1, carry);
                H1->trees[i] = NULL;
                break;
            case 6:
                carry = CombineTrees(T2, carry);
                H2->trees[i] = NULL;
                break;
            case 7:
                H1->trees[i] = carry;
                carry = CombineTrees(T1, T2);
                H2->trees[i] = NULL;
                break;
            default:
                break;
        }
    }

    DisposeBinQueue(H2);

    return H1;
}

BinQueue Insert(BinQueue H, ElementType X) {
    BinQueue H1;
    BinTree T;

    T = (BinTree)malloc(sizeof(BinNode));
    T->val = X;
    T->first_child = T->next_sibling = NULL;

    H1 = InitBinQueue();
    H1->size = 1;
    H1->trees[0] = T;

    return Merge(H, H1);
}

void PrintTree(BinTree T, int number) {
    LevelOrderTraversal(T, 0);
    for (int i = 0; i <= number; i++) {
        for (int j = 1; j <= F[i][0]; j++) {
            printf("%d,", F[i][j]);
        }
    }
}

void LevelOrderTraversal(BinTree T, int level) {
    if (T == NULL) {
        return;
    }
    LevelOrderTraversal(T->next_sibling, level);
    F[level][++F[level][0]] = T->val;
    LevelOrderTraversal(T->first_child, level + 1);
}

void DisposeBinQueue(BinQueue H) {
    for (int i = 0; i < MAX_SIZE; i++) {
        DisposeBinTree(H->trees[i]);
    }
    free(H);
}

void DisposeBinTree(BinTree T) {
    if (T != NULL) {
        DisposeBinTree(T->next_sibling);
        DisposeBinTree(T->first_child);
        free(T);
    }
}