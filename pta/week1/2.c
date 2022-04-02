/* Convert the infix expression to postfix expression. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef float ElementType;
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

int GetPriority(char X);

char _OUTPUT[50];
int _COUNT;

int main() {
    Stack S;
    char X;
    float A, B;

    S = CreateStack();

    while ((X = getchar()) != EOF) {
        if (isdigit(X)) {
            _OUTPUT[_COUNT++] = X;  // number goes to _OUTPUT
        } else if (X == ')') {
            while (Top(S) != '(') {
                _OUTPUT[_COUNT++] = Pop(S);  // when ')' is encounted, pop until '(' is found
            }
            Pop(S);  // pop the remaining '('
        } else if (X == '+' || X == '-' || X == '*' || X == '/' || X == '(') {
            while (Top(S) != '(' && (GetPriority(X) <= GetPriority(Top(S)))) {
                _OUTPUT[_COUNT++] = Pop(S);  // pop until a symbol of lower priority is found
            }
            Push(X, S);
        }
    }

    // pop the rest symbols in stack
    while (!IsEmpty(S)) {
        _OUTPUT[_COUNT++] = Pop(S);
    }

    // calculte the postfix expression
    for (int i = 0; i < _COUNT; i++) {
        if (isdigit(_OUTPUT[i])) {
            Push(_OUTPUT[i] - '0', S);
        } else {
            B = Pop(S);
            A = Pop(S);
            switch (_OUTPUT[i]) {
                case '+':
                    Push(A + B, S);
                    break;
                case '-':
                    Push(A - B, S);
                    break;
                case '*':
                    Push(A * B, S);
                    break;
                case '/':
                    Push(A / B, S);
                    break;
                default:
                    break;
            }
        }
    }

    // _OUTPUT
    printf("%.2f\n", Pop(S));
    for (int i = 0; i < _COUNT; i++) {
        printf("%c ", _OUTPUT[i]);
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

int GetPriority(char X) {
    switch (X) {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '(':
            return 3;
            break;
        default:
            return 0;
            break;
    }
}