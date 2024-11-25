/*
В соответствии с вариантом, необходимо рассчитать и вывести на экран значение, рассчитанное с помощью ассемблерной вставки применяя команды сравнения и перехода. 
Все переменные являются целочисленными и вводятся пользователем с клавиатуры.
Z = A*( B+C) если Z = 0, то вычислить C/ (A+B) +B иначе вычислить  (A-B)!
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
  int A, B, C, res, res1;
  printf("Input A, B, C values:\n");
  scanf("%d %d %d", &A, &B, &C);
  int Z = A * (B + C);
  if (Z == 0 && A + B == 0){
    printf("\nUncorrect input! Devision by zero!");
    return 1;
  }
  if (Z != 0 && A - B < 0){
    printf("\nUncorrect input! factorial!");
    return 2;
  }
  printf("\nEcho output:\n");
  printf("A = %d; B = %d; C = %d;\n", A, B, C);
  A
  asm(
  // Расчёт Z = A * (B + C) 
  "movl %1, %%eax;" // B -> EAX
  "movl %2, %%ebx;" // C -> EBX
  "addl %%eax, %%ebx;" // B + C -> EBX
  "movl %3, %%eax;" // A -> EAX
  "imull %%ebx;" // EAX * EBX =  A * (B + C) -> EAX
  "movl $0, %%ebx;" // 0 -> EBX
  
  "cmp %%ebx, %%eax;" // Сравнение ebx и 0
  "je equal;" // Z == 0 
  
  // Z != 0
  // Блок расчёта (A - B)!
  "movl %6, %%eax;" // A -> EAX
  "movl %4, %%ebx;" // B -> EBX
  "subl %%ebx, %%eax;" // A - B -> EAX
  "movl %%eax, %%ebx;" // EAX -> EBX
  "movl $0, %%ecx;" // 0 ->  ECX (счётчик)
  "movl $1, %%eax;" // 1 -> EAX (факториал)
  
  
  "loop_start:" // Начало цикла
  "addl $1, %%ecx;" // Прибавляем счётчик
  "imul %%ecx;" // eax = eax * ecx
  "cmp %%ecx, %%ebx;" // Cравниваем с нужным факториалом
  "jne loop_start;" // Если не равен повторить цикл
  "jmp exit;"
  
  "equal:" //  C / (A + B) + B
  "movl %6, %%eax;" // A -> EAX
  "movl %4, %%ebx;" // B -> EBX
  "addl %%eax, %%ebx;" // (A + B) -> EAX
  "movl %5, %%eax;" // C -> EBX
  "cdq;"
  "idiv %%ebx;"
  "movl %4, %%ebx;"
  "addl %%ebx, %%eax;"
  "jmp exit;"
  
  "exit:"
  "movl %%eax, %0;"
  
  :"=r"(res)
  :"r"(B), "r"(C), "r"(A), "r"(B), "r"(C), "r"(A)
  : "%eax", "%ebx", "%ecx"
  );
  
  printf("asm result = %d \n", res);
  
  if (Z == 0){
A;
  }
  else{
      int count = A - B;
      res1 = 1;
      for (int i = 1; i <= count; i++){
          res1 = res1 * i;
      }
  }
  printf("asm result = %d \n", res);
  printf("C result = %d ", res1);
  return 0;
}
