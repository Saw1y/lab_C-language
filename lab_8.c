*/
В каждом варианте задания требуется создать целочисленный динамический двумерный массив, который может становиться «неправильной формы», т.е. каждая строка которого 
может быть своей длины, причём индексация строк начинается с 1, а в нулевом элементе хранится общее количество элементов данной строки. В начале массив генерируется 
заданного пользователем размера A x B с элементами заданными случайным образом из заданного пользователем диапазона, а все строки которого изначально будут одинаковой 
длины B. В последствии необходимо к каждой строке применить одну из 4-х функций по модификации одномерного динамического массива (по классу задач: удаление, 
добавление, перестановка, поиск), заданных ниже по-вариантно, и в результате удаления\вставок элементов каждая строка может изменять свой размер. Функции к 
строкам применяются последовательно: т.е. функция «удаление» применяется к 1 строке двумерного массива, функция «добавление» применяется ко 2 строке, функция 
«перестановка» применяется к 3 строке, функция «поиск» применяется к 4 строке, функция «удаление» применяется к 5 строке, функция «добавление» применяется к 6 
строке и т.д. При добавлении элементов соответственно строки динамического массива должны расширяться, а при удалении элементов – уменьшаться. Весь текстовый 
ввод\вывод должен осуществляться в консоль исключительно из основной функции main. 

Важно:   
1) Функции работают с указателями на динамические одномерные массивы, т.е. строки 
двумерного массива мы передаём построчно для обработки в функции как одномерные 
массивы через указатели. 
2) Функции работают с целочисленными динамическими одномерными массивами где 
индексы начинаются с 1, а в 0-вом элементе записан текущий размер динамического 
массива. При удалении\добавлении элементов функции должны записать новый размер 
массива в 0-вой элемент. 
3) В функциях будет более удобно использовать арифметику указателей и относительные 
смещения. 
4) При добавлении случайных элементов по заданию нужно использовать тот же 
диапазон генерации, который задал пользователь для генерации исходного двумерного 
массива. 
5) Циклический сдвиг вправо или влево – это когда элементы из конца или начала 
массива переходят соответственно в его начало или конец.
/*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fill_random(int** const arr, int const A, int const left, int const right)
{
    srand(time(NULL));
    int i;
    int j;
    for (i = 0; i < A; i++)
    {
        for (j = 1; j <= arr[i][0]; j++)
        {
            arr[i][j] = left + rand() % (right - left + 1);
        }
    }
}


void print_array(int** const arr, int A) {
  int i;
  int j;
    for (i = 0; i < A; i++)
    {
        for (j = 1; j <= arr[i][0]; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int* deleting(int* row) {
    int i = 1;
    while (i <= row[0]) {
        if (row[i] % 2 == 0) {
            row[i] = row[row[0]]; 
            row[0]--;            
        } else {
            i++;
        }
    }
    row = realloc(row, (row[0] + 1) * sizeof(int));
    return row;
}


int* add(int* const row, int const left, int const right) {
    int count = 0;
    int j;
    for (j = 1; j <= row[0]; j++) {
        if (row[j] < 0) {
            count++;
        }
    }

    int new_size = row[0] + count;
    int* new_row = (int*)malloc((new_size + 1) * sizeof(int)); 
    new_row[0] = new_size; 

    int index = 1; 
    for (j = 1; j <= row[0]; j++) {
        new_row[index++] = row[j]; 
        if (row[j] < 0) {
            new_row[index++] = left + rand() % (right - left + 1); 
        }
    }

    free(row); 
    return new_row; 
}


int* rearrangement(int* const row) {
    int left = 1;
    int right = row[0]; 
    while (left < right) {
        while (left <= row[0] && row[left] >= 0) {
            left++;
        }
        while (right > 0 && row[right] <= 0) {
            right--;
        }
        if (left < right) {
            int temp = row[left];
            row[left] = row[right];
            row[right] = temp;
        }
    }
    return row;
}

int *find(int* const row)
{
  int i;
  int ind = -1;
  for (i = 1; i <= row[0]; i++)
  {
    if (row[i] < 0 )
    {
      ind = i;
    }
  }
  if (ind != -1)
  {
    row[ind] = 0;
  }
  return row;
}


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
