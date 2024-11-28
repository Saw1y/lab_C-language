#define arr_type int
#define string_type "%d"
#define ELEM(arr, i) arr[i + 1]
#define LEN(arr) arr[0]
//#define FIND_FIRST

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs1.inc"

int main() {
    int left, right, A, B;
    do {
        printf("Enter the number of rows (A): ");
        scanf("%d", &A);
        printf("Enter the number of columns (B): ");
        scanf("%d", &B);
    } while (A <= 0 || B <= 0);

    do {
        printf("Enter the minimum value: ");
        scanf("%d", &left);
        printf("Enter the maximum value: ");
        scanf("%d", &right);
    } while (left > right);

    int** arr = (int**)malloc(A * sizeof(int*));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }
    int i;
    for (i = 0; i < A; i++) {
        arr[i] = (int*)malloc((B + 1) * sizeof(int));
        if (!arr[i]) {
            printf("Memory allocation failed\n");
            return 1;
        }
        arr[i][0] = B;
    }

    fill_random(arr, A, left, right);
    printf("Array after filling:\n");
    print_array(arr, A);

    for (i = 0; i < A; i++)
{
      if (i % 4 == 0)
    {
        arr[i] = deleting(arr[i]);
        printf("Array after deleting in %d line:\n", i + 1);
        print_array(arr, A);
    }
      if (i % 4 == 1)
    {
        arr[i] = add(arr[i], left, right);
        printf("Array after add in %d line:\n", i + 1);
        print_array(arr, A);
    }
      if (i % 4 == 2)
    {
        arr[i] = rearrangement(arr[i]);
        printf("Array after rearrangement in %d line:\n", i + 1);
        print_array(arr, A);
    }
    if (i % 4 == 3)
    {
      arr[i] = find(arr[i]);
      printf("Array after find in %d line:\n", i + 1);
        print_array(arr, A);
    }
}
    for (i = 0; i < A; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
