/* 
Табулируйте функцию двух аргументов с форматированным выводом таблицы значений и найдите те значения аргументов, при которых функция принимает 
максимальное и минимальное значение в заданном диапазоне. В заданиях функция f табулируется по аргументам x [x0 (xh) xn] и y[y0 (yh) yn], а 
параметры а, nm1, nm2 вводятся пользователем произвольно, причём nm1, nm2  [2,6]  При проектировании алгоритма программы применить нисходящее проектирование. 
*/
#include <stdio.h> 
#include <math.h> 
#include <stdbool.h> 
#include <float.h> 

bool Input_correct(int nm1, int nm2, float x0, float xn, float y0, float yn, float yh, float xh) { 
 if (nm1 >= 2 && nm1 <= 6 && nm2 >= 2 && nm2 <= 6 && x0 <= xn && y0 <= yn && xh > 0 && yh > 0) { 
  return true; 
 } else { 
  return false; 
 } 
} 


double Solve1(float x, float y, int nm1)
{
    int res = 0;
    int n = 1;
    while (n <= nm1)
    {
        res += (1 + pow((y * x + 1), n) / (n + 4));
        n++;
    }
    res = (x + y) / (pow(x ,2)  +4) * res;
    return res;
}

double Solve2(float x, float y, int nm2)
{   
    int res = 1;
    int n = 1;
    while (n <= nm2)
    {
        res *= ((x * y)  + (pow(2 * x + 1, n ) / pow(2 * n + 3 * y, 0.5)));
        n++;
    }

    res = (x + 1) / y * res;
    return res;
}
int main(){
    // Объявление переменных 
    float x0, xh, xn;
    float y0, yh, yn;
    float x, y;
    double result, a;
    double max, min;
    int nm1, nm2;

    // Ввод переменных
    printf("Input [x0 (xh) xn]: \n"); 
    scanf("%f %f %f", &x0, &xh, &xn); 
  
    printf("Input [y0 (yh) yn]: \n"); 
    scanf("%f %f %f", &y0, &yh, &yn); 
  
    printf("Input values of a, nm1, nm2: \n"); 
    scanf("%le %d %d", &a, &nm1, &nm2); 
    // Проверка
    if (Input_correct(nm1, nm2, x0, xn, y0, yn, yh, xh) == 0)
    { 
    printf("Incorrect input of values"); 
    return 1; 
    }
    // Вычисления
    x = x0;
    y = y0;
    float xmax = x0; 
    float ymax = y0; 
    float xmin = x0; 
    float ymin = y0;
    max = - FLT_MAX; 
    min = FLT_MAX; 
    // Вывод шапки таблицы
    printf("--------------------------------\n"); 
    printf("|   x   |   y   |    Result    |\n"); 
    printf("--------------------------------\n");
    while (x <= xn)
    {
        y = y0;
        while (y <= yn)
        {
            if (fabs(x) < a)
            {
                result = Solve1(x, y, nm1);
            } 

            else
            {
                result = Solve2(x, y, nm2);
            }
            if (result < min){
                min = result;
                xmin = x;
                ymin = y;
            }
            if (result > max){
                max = result;
                xmax = x;
                ymax = y;
            }
            printf("| %10.3f | %10.3f | %10.3f | \n", x, y, result); 
            printf("--------------------------------\n"); 

            y += yh;
        }
        
        x += xh;
    }
    
    printf("Minimal result = %le, in point (%f, %f) \n", min, xmin, ymin); 
    printf("Maximal result = %le, in point (%f, %f)", max, xmax, ymax); 

    return 0;
}
