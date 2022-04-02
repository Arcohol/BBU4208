/* Inserting some numbers into an initially empty AVL tree. Show the AVL tree in preorder. */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AvlNode {
    ElementType val;
    struct AvlNode *left, *right;
    int height;
} AvlNode;
typedef AvlNode *Position;
typedef AvlNode *AvlTree;

AvlTree Insert(ElementType X, AvlTree T);
void Preorder(AvlTree T);
void DisposeTree(AvlTree T);

int Height(Position P);
int Max(int a, int b);
Position Rotate_LL(Position K2);
Position Rotate_RR(Position K2);
Position Rotate_LR(Position K3);
Position Rotate_RL(Position K3);

int main() {
    AvlTree T = NULL;
    int val;

    while (scanf("%d,", &val) != EOF) {
        T = Insert(val, T);
    }

    Preorder(T);

    DisposeTree(T);

    return 0;
}

int Height(Position P) { return P == NULL ? -1 : P->height; }

int Max(int a, int b) { return a > b ? a : b; }

AvlTree Insert(ElementType X, AvlTree T) {
    if (T == NULL) {
        T = (AvlTree)malloc(sizeof(AvlNode));
        T->val = X;
        T->left = T->right = NULL;
        T->height = 0;
    } else if (X < T->val) {
        T->left = Insert(X, T->left);

        if (Height(T->left) - Height(T->right) == 2) {
            if (X < T->left->val) {
                T = Rotate_LL(T);
            } else {
                T = Rotate_LR(T);
            }
        }
    } else if (X > T->val) {
        T->right = Insert(X, T->right);

        if (Height(T->right) - Height(T->left) == 2) {
            if (X > T->right->val) {
                T = Rotate_RR(T);
            } else {
                T = Rotate_RL(T);
            }
        }
    }

    // update height after insertion
    T->height = Max(Height(T->left), Height(T->right)) + 1;

    return T;
}

void Preorder(AvlTree T) {
    if (T != NULL) {
        printf("%d,", T->val);
        Preorder(T->left);
        Preorder(T->right);
    }
}

void DisposeTree(AvlTree T) {
    if (T != NULL) {
        DisposeTree(T->left);
        DisposeTree(T->right);
        free(T);
    }
}

Position Rotate_LL(Position K2) {
    Position K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    // update height
    K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
    K1->height = Max(Height(K1->left), Height(K1->right)) + 1;

    // K1 is the new root
    return K1;
}

Position Rotate_RR(Position K2) {
    Position K1 = K2->right;
    K2->right = K1->left;
    K1->left = K2;

    // update height
    K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
    K1->height = Max(Height(K1->left), Height(K1->right)) + 1;

    // K1 is the new root
    return K1;
}

Position Rotate_LR(Position K3) {
    Position K2 = K3->left, K1 = K2->right;
    K2->right = K1->left;
    K3->left = K1->right;
    K1->left = K2;
    K1->right = K3;

    // update height
    K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
    K3->height = Max(Height(K3->left), Height(K3->right)) + 1;
    K1->height = Max(Height(K1->left), Height(K1->right)) + 1;

    // K1 is the new root
    return K1;
}

Position Rotate_RL(Position K3) {
    Position K2 = K3->right, K1 = K2->left;
    K2->left = K1->right;
    K3->right = K1->left;
    K1->left = K3;
    K1->right = K2;

    // update height
    K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
    K3->height = Max(Height(K3->left), Height(K3->right)) + 1;
    K1->height = Max(Height(K1->left), Height(K1->right)) + 1;

    // K1 is the new root
    return K1;
}