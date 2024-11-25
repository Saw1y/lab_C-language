/*
Для приведенных ниже заданий составить две функции вычисления: с использованием 
рекурсии и итерации.
Вычислить S1 – S2, где S1 – сумма нечетных целых чисел от N1 до N2, S2 – сумма 
четных чисел от M1 до M2. 
*/

#include <stdio.h>
#include <stdlib.h>
long solve1(long n1, long n2, long m1, long m2)
{
    long s1 = 0;
    long s2 = 0;
    long res = 0;
    while (n1 < n2)
    {
        if (labs(n1) % 2 != 0){
            s1 = s1 + n1;
        }
        n1++;
    }
    
    while (m1 < m2)
    {
        if (labs(m1) % 2 == 0){
            s2 = s2 + m1;
        }
        m1++;
    }
    res = s1 - s2;
    return res;
}

long recursion1(long n1 ,long n2, long count)
{
    if (n1 >= n2){
        return count;
    }
    else
    {
        if (labs(n1) % 2 != 0){
            return recursion1(n1 + 1, n2, count + n1);
        }
        else{
            return recursion1(n1 + 1, n2, count);
        }
    }
    
}
long recursion2(long m1 ,long m2, long count)
{
    if (m1 >= m2){
        return count;
    }
    else
    {
        if (labs(m1) % 2 == 0){
            return recursion2(m1 + 1, m2, count + m1);
        }
        else{
            return recursion2(m1 + 1, m2, count);
        }
    }
    
}


long solve2(long n1, long n2, long m1, long m2)
{
    long s1 = recursion1(n1, n2, 0);
    long s2 = recursion2(m1, m2, 0);
    long res = s1 - s2;
    return res;
}

int main()
{
    long n1;
    long n2;
    long m1;
    long m2;
    long res1;
    long res2;
    do {
    printf("Input n1: ");
    scanf("%ld" ,&n1);
    printf("Input n2: ");
    scanf("%ld" ,&n2);
    printf("Input m1: ");
    scanf("%ld" ,&m1);
    printf("Input m2: ");
    scanf("%ld" ,&m2);
    } while(n1 >= n2 || m1 >= m2);
    res1 = solve1(n1, n2, m1, m2);
    res2 = solve2(n1, n2, m1, m2);
    printf("%ld \n", res1);
    printf("%ld", res2);
    return 0;
}
