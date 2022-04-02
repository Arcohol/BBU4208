/* A binary search tree is a binary tree. It may be empty. If it is not empty, it satisfies the
 * following properties:
 * (1) Every node has a key which is an integer, and the keys are distinct.
 * (2) The keys in a nonempty left subtree must be smaller than the key in the root of the subtree.
 * (3) The keys in a nonempty right subtree must be larger than the key in the root of the subtree.
 * (4) The left and right subtrees are also binary search trees.

 * Give a sequence of distinct integer to build the binary search tree, and output the nodes on
 * particular level. */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode {
    ElementType val;
    struct TreeNode *left, *right;
} TreeNode;
typedef TreeNode *SearchTree;

SearchTree Insert(ElementType X, SearchTree T);
void Preorder(SearchTree T, int L);
void DisposeTree(SearchTree T);

int _LEVEL, _ELEMENT_FOUND;

int main() {
    SearchTree T = NULL;
    int count, val;

    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        scanf("%d,", &val);
        T = Insert(val, T);
    }

    scanf("%d", &_LEVEL);

    Preorder(T, 1);

    if (!_ELEMENT_FOUND) {
        printf("-1");
    }

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

void Preorder(SearchTree T, int L) {
    if (T != NULL) {
        if (L == _LEVEL) {
            printf("%d,", T->val);
            _ELEMENT_FOUND++;
            return;
        }
        Preorder(T->left, L + 1);
        Preorder(T->right, L + 1);
    }
}

void DisposeTree(SearchTree T) {
    if (T != NULL) {
        DisposeTree(T->left);
        DisposeTree(T->right);
        free(T);
    }
}