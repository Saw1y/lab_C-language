/*
Преобразовать лабораторную работу №4 таким образом, чтобы работа с массивами, и их 
передача в качестве параметров в функции велась только через арифметику указателей. 
Выбор функции заполнения массива необходимо осуществлять через указатель на 
функцию.
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// specifying a coordinate array through direct input of coordinates from the keyboard
void Input_array1(float* const arr, const int sizeX)
{
 
 int i;
 float x, y;
 
 for (i = 0; i < sizeX; i++)
 {
  printf("arr[%d] = ", i);
  scanf("%f %f", &x, &y);
  *(arr + i * 2) = x;
  *(arr + i * 2 + 1) = y;
 }
}

// specify the coordinate array randomly within the specified range
void Input_array2(float* const arr, const int sizeX, const float left, const float right)
{
  srand(time(0));
  int i;
  for (i = 0; i < sizeX; i++)
  {
 *(arr + i * 2) = (float)rand() / RAND_MAX * (right - left) + left;
 *(arr + i * 2 + 1) = (float)rand() / RAND_MAX * (right - left) + left;
  }
}


bool Hit_point(const float x, const float y, const float r)
{
  float eps = 10e-6;
  float dist = x * x + y * y;
  bool flag = false;
  
  if (dist + eps <= r * r)
  {
    if (x < 0  && y  > 1 / x){
      flag = true;
    }
    if (x > 0  && y < 1 / x){
      flag = true;
    }
  }
  return flag;
        
} 
void PrintPoints(const float* const arr, const int sizeX, const float rad)
{
  int i;
  for (i = 0; i < sizeX; i++)
  {
    if(Hit_point(*(arr + i * 2), *(arr + i * 2 + 1), rad))
    {
      printf("The point with coordinates x = %.2f, y = %.2f falls into the selected area\n", *(arr + i * 2), *(arr + i * 2 + 1));
    } 
    else
    {
      printf("The point with coordinates x = %.2f, y = %.2f not falls into the selected area\n", *(arr + i * 2), *(arr + i * 2 + 1));
    }
  }
}

int main() {
  
  int coords; 
  int choice;
  float rad; 
  
  do
  {
    printf("Input the number of dots: ");
    scanf("%d", &coords);
    printf("\n"); 
  } while(coords <= 0);
  
  float array[coords][2];
  do
  {
    printf("1. Direct input of coordinates from the keyboard\n");
    printf("2. Setting the coordinate array randomly\n");
    printf("Select a way to set the array: ");
    scanf("%d", &choice);
    printf("\n");
  } while(choice > 2 || choice < 1);
  
  if (choice  == 1)
  {
    Input_array1( (float*) array, coords);
  }
  else
  {
    float a;
    float b; 
    do 
    {
      printf("Generating range entry: \n");
      scanf("%f", &a);
      scanf("%f", &b);

    } while(a >= b);

    printf("a = %f, b = %f\n", a, b);
    Input_array2((float*) array, coords, a, b);
  }

  do
  {
    printf("Enter radius: ");
    scanf( "%f", &rad);
  } while(rad <= 0);
  PrintPoints((float*) array, coords, rad);
  return 0;
}
