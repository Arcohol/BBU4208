/* Given a sequence of numbers seperated by comma, you should sort them by radix sort. Output the
 * step result of each pass. */

#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 20

void RadixSort(int A[], int N);
int GetMax(int A[], int N);
void CountingSort(int A[], int N, int exp);
void PrintArray(int A[], int N);

int _N;
int main() {
    int A[MAX_NUMBER], i;
    char str[100], *tmp;

    scanf("%s", str);

    tmp = strtok(str, ",");
    for (i = 0; i < MAX_NUMBER && tmp != NULL; i++) {
        A[i] = atoi(tmp);
        tmp = strtok(NULL, ",");
    }

    scanf("%d", &_N);

    RadixSort(A, i);

    return 0;
}

void RadixSort(int A[], int N) {
    int max;

    max = GetMax(A, N);
    for (int exp = 1, i = 1; max / exp > 0; exp *= 10, i++) {
        CountingSort(A, N, exp);
        if (i == _N) {
            PrintArray(A, N);
        }
    }
}

int GetMax(int A[], int N) {
    int max;

    max = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }

    return max;
}

void CountingSort(int A[], int N, int exp) {
    int output[N];
    int i, count[10] = {0};

    for (i = 0; i < N; i++) {
        count[A[i] / exp % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = N - 1; i >= 0; i--) {
        output[--count[A[i] / exp % 10]] = A[i];
    }
    for (i = 0; i < N; i++) {
        A[i] = output[i];
    }
}

void PrintArray(int A[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d,", A[i]);
    }
    putchar('\n');
}