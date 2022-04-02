#include <stdio.h>
#include <string.h>

#define STR_MAX_SIZE 200
#define PAT_MAX_SIZE 20

void KMP(char str[], char pat[], int next[]);
void GetNext(char pat[], int next[]);

int main() {
    char str[STR_MAX_SIZE + 2] = {0}, pat[PAT_MAX_SIZE + 2] = {0};
    int next[PAT_MAX_SIZE + 2] = {0}, pos = 1, count = 0;

    scanf("%s", str + 1);
    str[0] = strlen(str + 1);

    scanf("%s", pat + 1);
    pat[0] = strlen(pat + 1);

    GetNext(pat, next);

    for (int i = 1; i <= pat[0]; i++) {
        printf("%d,", next[i]);
    }
    putchar('\n');

    KMP(str, pat, next);

    return 0;
}

void KMP(char str[], char pat[], int next[]) {
    int i = 1, j = 1, count = 0;

    while (i <= str[0]) {
        if (j == 0 || str[i] == pat[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }

        if (j > pat[0]) {
            printf("%d\n", i - pat[0]);
            count++;
            i -= next[pat[0] + 1] - 1;
            j = 1;
        }
    }

    if (!count) {
        printf("-1\n");
    }
}

void GetNext(char pat[], int next[]) {
    int k = 0, j = 1;

    next[1] = 0;
    while (j <= pat[0]) {
        if (k == 0 || pat[k] == pat[j]) {
            next[++j] = ++k;
        } else {
            k = next[k];
        }
    }
}