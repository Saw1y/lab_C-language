/*
Выполнить задание по вариантам с использованием динамических одномерных 
массивов, используя команды выделения памяти malloc и освобождения free. Каждое 
действие с массивами оформить в виде отдельных функций. Для всех массивов можно 
выделить память одного размера. 

Создайте динамический массив чисел A, заполненный случайными 
значениями. Создайте новый динамический массив B, содержащий только числа, которые 
являются простыми из массива A. Отсортируйте элементы массива B в порядке 
возрастания. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Input_array(int* const arr, const int sizeX, const int left, const int right) {
    srand(time(0));
    for (int i = 0; i < sizeX; i++) {
        arr[i] = left + rand() % (right - left + 1);
    }
}

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void Input_Prime_array(int* const arr_1, int* const arr_2, int size_1) {
    int j = 0;
    int i;
    for (i = 0; i < size_1; i++) {
        if (isPrime(arr_1[i])) {
            arr_2[j++] = arr_1[i];
        }
    }
}

void print_array(int* arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_array(int* arr, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        bool swap = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap = true;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (swap == false){
            break;
        }
    }
}

int main() {
    int size_A = 0;
    int left = 0;
    int right = 0;
    int *A = NULL;
    int *B = NULL;
    int count = 0;

    do {
        printf("Input size array A: ");
        scanf("%d", &size_A);
    } while (size_A <= 0);

    do {
        printf("Generating range entry (left right): \n");
        scanf("%d %d", &left, &right);
    } while (left >= right || left < 0);

    A = malloc(sizeof(int) * size_A);

    Input_array(A, size_A, left, right);
    printf("Array A: ");
    print_array(A, size_A);
    
    int i = 0;
    for (i = 0; i < size_A ; i++){
        if (isPrime(A[i])){
            count++;
        }
    }

    if (count == 0) {
        printf("In array A there are no prime integers.\n");
        free(A);
        return 1;
    }
    B = malloc(sizeof(int) * count); // Выделяем память для массива B

    Input_Prime_array(A, B, size_A);
    free(A);
    printf("Count of prime numbers: %d\n", count);
    printf("Array B (before sorting): ");
    print_array(B, count);

    sort_array(B, count);

    printf("Array B (after sorting): ");
    print_array(B, count);

    free(B);
    return 0;
}
