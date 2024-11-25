/*
Дан массив координат, необходимо определить какие из этих координат попадают в заданную закрашенную область, а какие не попадают, и вывести эту информацию на 
экран. Массив координат задаётся двумерным массивом, где первый индекс означает номер координаты, а второй номер компоненты координаты (x – 0, y - 1). 
Массив задаётся по выбору пользователя либо через непосредственный ввод координат с клавиатуры, либо случайным образом в заданном пользователем диапазоне.  

В программе должно быть минимум четыре отдельных функции:  
1. Задание массива координат через непосредственный ввод координат с 
клавиатуры. 
2. Задание массива координат случайным образом в заданном диапазоне. 
3. Определение попадание точки в заданную область. 
4. Вывод попавших и не попавших координат в область.  
Параметры R, a и b, задающие область, а также количество координат задаются 
пользователем.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// specifying a coordinate array through direct input of coordinates from the keyboard
void Input_array1(float arr[][2], const int sizeX, const int sizeY)
{
  float elem;
  int i, j;
  for (i = 0; i < sizeX; i++){
    for (j = 0; j < sizeY; j++){
      printf("array[%d][%d] = ", i, j);
      scanf("%f", &elem);
      arr[i][j] = elem;
    }
  }
}
// specify the coordinate array randomly within the specified range
void Input_array2(float arr[][2], const int sizeX, const int sizeY, const float left, const float right)
{
  srand(time(0));
  int i, j;
  float elem;
  for (i = 0; i < sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      elem = (float)rand() / RAND_MAX * (right - left) + left;
      printf("arr[%d][%d] = %.2f\n", i, j, elem);
      arr[i][j] = elem;
    }
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
void PrintPoints(const float arr[][2], const int sizeX, const float rad)
{
  int i;
  for (i = 0; i < sizeX; i++)
  {
    if(Hit_point(arr[i][0], arr[i][1], rad))
    {
      printf("The point with coordinates x = %.2f, y = %.2f falls into the selected area\n", arr[i][0], arr[i][1]);
    } 
    else
    {
      printf("The point with coordinates x = %.2f, y = %.2f not falls into the selected area\n", arr[i][0], arr[i][1]);
    }
  }
}

int main() {
  // initialization of variables
  float array[100][2];
  int coords; 
  int choice;
  float rad; 
  
  do
  {
    printf("Input the number of dots:");
    scanf("%d", &coords);
    printf("\n"); 
  } while(coords <= 0);
  
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
    Input_array1(array, coords, 2);
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
    Input_array2(array, coords, 2, a, b);
  }

  do
  {
    printf("Enter radius: ");
    scanf( "%f", &rad);
  } while(rad <= 0);
  
  PrintPoints(array, coords, rad);
  return 0;
}
