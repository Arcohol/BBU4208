/* Balancing symbols: Check if parenthesis(), brackets[], and braces{} are balanced. */

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct Node {
    ElementType val;
    struct Node *next;
} Node;
typedef Node *Stack;

Stack CreateStack();
int IsEmpty(Stack S);
void Push(ElementType val, Stack S);
ElementType Pop(Stack S);
ElementType Top(Stack S);
void DisposeStack(Stack S);

int IsSymbol(char X);
int IsMatch(char A, char B);
void Count(char X);

int _COUNT[3];
char _MAP[] = {'1', '2', '3'};

int main() {
    Stack S;
    char X;

    S = CreateStack();

    while ((X = getchar()) != EOF) {
        if (!IsSymbol(X)) {
            continue;  // skip non-symbol
        }

        if (IsSymbol(X) == 1) {
            Push(X, S);  // push left-symbol
        } else {
            if (IsEmpty(S)) {
                Count(X);  // count the incoming symbol if stack is empty
            } else {
                if (!IsMatch(Top(S), X)) {
                    Count(Pop(S));  // pop and count both if two symbols do not match
                    Count(X);
                } else {
                    Pop(S);  // pop if if two symbols match
                }
            }
        }
    }

    // pop and count the rest symbols in stack
    while (!IsEmpty(S)) {
        Count(Pop(S));
    }

    // output
    if (!_COUNT[0] && !_COUNT[1] && !_COUNT[2]) {
        putchar('0');
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < _COUNT[i]; j++) {
                printf("%c,", _MAP[i]);
            }
        }
    }

    DisposeStack(S);

    return 0;
}

Stack CreateStack() {
    Stack S;

    S = (Stack)malloc(sizeof(Node));
    S->val = -1;
    S->next = NULL;

    return S;
}

int IsEmpty(Stack S) { return S->next == NULL; }

void Push(ElementType val, Stack S) {
    Node *new_node;

    new_node = (Node *)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = S->next;
    S->next = new_node;
}

ElementType Pop(Stack S) {
    ElementType top_val;
    Node *top_node;

    if (IsEmpty(S)) {
        return 0;
    }

    top_val = S->next->val;

    top_node = S->next;
    S->next = S->next->next;

    free(top_node);

    return top_val;
}

ElementType Top(Stack S) { return IsEmpty(S) ? 0 : S->next->val; }

void DisposeStack(Stack S) {
    while (!IsEmpty(S)) {
        Pop(S);
    }
    free(S);
}

int IsSymbol(char X) {
    if (X == '(' || X == '[' || X == '{') {
        return 1;
    } else if (X == ')' || X == ']' || X == '}') {
        return 2;
    } else {
        return 0;
    }
}

int IsMatch(char A, char B) {
    switch (A) {
        case '(':
            return B == ')';
            break;
        case '[':
            return B == ']';
            break;
        case '{':
            return B == '}';
            break;
        default:
            return 0;
            break;
    }
}

void Count(char X) {
    if (X == '(' || X == ')') {
        _COUNT[0]++;
    } else if (X == '[' || X == ']') {
        _COUNT[1]++;
    } else if (X == '{' || X == '}') {
        _COUNT[2]++;
    } else {
        return;
    }
}