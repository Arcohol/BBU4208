/* A binary search tree is a binary tree. It may be empty. If it is not empty, it satisfies the
 * following properties:
 * (1) Every node has a key which is an integer, and the keys are distinct.
 * (2) The keys in a nonempty left subtree must be smaller than the key in the root of the subtree.
 * (3) The keys in a nonempty right subtree must be larger than the key in the root of the subtree.
 * (4) The left and right subtrees are also binary search trees.

 * Given a sequence of distinct integers to build the binary search tree, and traverse the tree by
 * Preorder. */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode {
    ElementType val;
    struct TreeNode *left, *right;
} TreeNode;
typedef TreeNode *SearchTree;

SearchTree Insert(ElementType X, SearchTree T);
void Preorder(SearchTree T);
void DisposeTree(SearchTree T);

int main() {
    SearchTree T = NULL;
    int val;

    while (scanf("%d,", &val) != EOF) {
        T = Insert(val, T);
    }

    Preorder(T);

    DisposeTree(T);

    return 0;
}

SearchTree Insert(ElementType X, SearchTree T) {
    if (T == NULL) {
        T = (SearchTree)malloc(sizeof(TreeNode));
        T->val = X;
        T->left = T->right = NULL;
    } else if (X < T->val) {
        T->left = Insert(X, T->left);
    } else if (X > T->val) {
        T->right = Insert(X, T->right);
    }

    return T;
}

void Preorder(SearchTree T) {
    if (T != NULL) {
        printf("%d,", T->val);
        Preorder(T->left);
        Preorder(T->right);
    }
}

void DisposeTree(SearchTree T) {
    if (T != NULL) {
        DisposeTree(T->left);
        DisposeTree(T->right);
        free(T);
    }
}