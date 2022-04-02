/* Use Shell sort algorithm and Shell Increment Sequence to sort a sequence in descending orders. */

#include <stdio.h>
#include <stdlib.h>

void ShellSort(int A[], int N);
void PrintArray(int A[], int N);

int main() {
    int N, *A;

    scanf("%d", &N);

    A = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
        scanf("%d,", &A[i]);
    }

    ShellSort(A, N);

    free(A);

    return 0;
}

void ShellSort(int A[], int N) {
    int tmp, i, j, increment;

    for (increment = N / 2; increment > 0; increment /= 2) {
        for (i = increment; i < N; i++) {
            tmp = A[i];
            for (j = i; j >= increment && A[j - increment] > tmp; j -= increment) {
                A[j] = A[j - increment];
            }
            A[j] = tmp;
        }
        PrintArray(A, N);
    }
}

void PrintArray(int A[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d,", A[i]);
    }
    putchar('\n');
}