/* According to the basic idea of quick sort algorithm descirbed on class, we will modify a little
 * bit of this algorithm. Only the first pivot is given by the input operation. The other pivots
 * will still use Median-of-Three patitioning method. The inithial sequence is
 * {49,38,65,97,76,13,27,50,2,8}. We will sort this sequence in ascending order. The parameter
 * Cutoff is 3. */

#include <stdio.h>

#define CUTOFF 3

int GetPivot(int A[], int left, int right);
void QuickSort(int A[], int N);
void InsertionSort(int A[], int index, int N);
void __QuickSort(int A[], int left, int right);
void PrintArray(int A[], int N);
void Swap(int *A, int *B);

int __A__[] = {49, 38, 65, 97, 76, 13, 27, 50, 2, 8}, __N__ = 10, __pivot__;

int main() {
    scanf("%d", &__pivot__);

    QuickSort(__A__, __N__);

    return 0;
}

int GetPivot(int A[], int left, int right) {
    int medium;

    if (__pivot__) {
        Swap(&A[__pivot__], &A[right]);
        return A[right];
    } else {
        medium = (left + right) / 2;
        if (A[left] > A[medium]) {
            Swap(&A[left], &A[medium]);
        }
        if (A[left] > A[right]) {
            Swap(&A[left], &A[right]);
        }
        if (A[medium] > A[right]) {
            Swap(&A[medium], &A[right]);
        }
        Swap(&A[medium], &A[right - 1]);
        return A[right - 1];
    }
}

void QuickSort(int A[], int N) { __QuickSort(A, 0, N - 1); }

void InsertionSort(int A[], int index, int N) {
    int tmp, i, j;

    for (i = index + 1; i < index + N; i++) {
        tmp = A[i];
        for (j = i; j > 0 && A[j - 1] > tmp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = tmp;
    }

    printf("insert(%d,%d):", index, N);
    PrintArray(__A__, __N__);
}

void __QuickSort(int A[], int left, int right) {
    int i, j, pivot;

    if (left + CUTOFF <= right) {
        pivot = GetPivot(A, left, right);
        i = __pivot__ ? left - 1 : left;
        j = __pivot__ ? right : right - 1;
        for (;;) {
            while (A[++i] < pivot) {
            }
            while (A[--j] > pivot) {
            }
            if (i < j) {
                Swap(&A[i], &A[j]);
            } else {
                break;
            }
        }
        Swap(&A[i], &A[(__pivot__ ? right : right - 1)]);  // restore pivot
        __pivot__ = 0;                                     // discard the specified pivot

        printf("Qsort(%d,%d):", left, right);
        PrintArray(__A__, __N__);

        __QuickSort(A, left, i - 1);
        __QuickSort(A, i + 1, right);
    } else {
        InsertionSort(A, left, right - left + 1);
    }
}

void PrintArray(int A[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d,", A[i]);
    }
    putchar('\n');
}

void Swap(int *A, int *B) {
    int tmp;

    tmp = *A;
    *A = *B;
    *B = tmp;
}