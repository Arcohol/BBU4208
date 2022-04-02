/* 设用于通信的电文由a到h共8个字母组成，字母在电文中出现的频率为7，19，2，6，32，3，21，10。
 * 根据这些频率做为权值构造哈夫曼树。用这棵哈夫曼树，将一串0和1组成的字符串，解码为其对应的字符。*/

#include <stdio.h>
#include <stdlib.h>

#define COUNT 20

typedef struct Node {
    char letter;
    struct Node *left, *right;
} Node;

int main() {
    Node *T[COUNT], *new, *scan;
    char X;

    for (int i = 0; i < COUNT; i++) {
        new = (Node *)malloc(sizeof(Node));
        new->letter = 0;
        new->left = new->right = NULL;
        T[i] = new;
    }

    T[0]->left = T[1];
    T[0]->right = T[2];
    T[1]->left = T[3];
    T[1]->right = T[4];
    T[2]->left = T[5];
    T[2]->right = T[6];
    T[5]->left = T[7];
    T[5]->right = T[8];
    T[7]->left = T[9];
    T[7]->right = T[10];
    T[8]->left = T[11];
    T[8]->right = T[12];
    T[9]->left = T[13];
    T[9]->right = T[14];
    T[3]->letter = 'b';
    T[4]->letter = 'g';
    T[6]->letter = 'e';
    T[10]->letter = 'd';
    T[11]->letter = 'a';
    T[12]->letter = 'h';
    T[13]->letter = 'c';
    T[14]->letter = 'f';

    scan = T[0];
    while ((X = getchar()) != EOF) {
        if (X == '0') {
            scan = scan->left;
        } else if (X == '1') {
            scan = scan->right;
        }
        if (scan->letter != 0) {
            putchar(scan->letter);
            scan = T[0];
        }
    }

    for (int i = 0; i < COUNT; i++) {
        free(T[i]);
    }

    return 0;
}