/*
Необходимо рассчитать и вывести на экран выражение и его значение, рассчитанное с помощью ассемблерной вставки. 
Переменные A, B, C, D, E, F являются целочисленными и вводятся пользователем с клавиатуры. Добавить в качестве проверки расчёт
данного выражения на С. Выражение (D - B) / (C + A) * D - A + E - F
*\

#include <stdio.h>
#include <stdlib.h>

int main() {
    int A, B, C, D, E, F, res1, res2;

    printf("Input A, B, C, D, E, F values:\n");
    scanf("%d%d%d%d%d%d", &A, &B, &C, &D, &E, &F);

    if (C + A == 0) {
        printf("Error!\n");
        return 1;
    }
    res1 = ((D - B) / (C + A)) * D - A + E - F;
	printf("The result of the calculation without assembler inserts: (%d - %d)/ (%d + %d) * %d - %d + %d - %d = %d\n", D, B, C, A, D, A, E, F, res1);
    asm (
        "movl %1, %%eax;"      /* eax = D */
        "movl %2, %%ebx;"      /* ebx = B */
        "subl %%ebx, %%eax;"   /* eax = D - B */
        
        "movl %3, %%ebx;"      /* ebx = C */
        "movl %4, %%ecx;"      /* ecx = A */
        "addl %%ebx, %%ecx;"   /* ecx = C + A */
        
        "cdq;"
        "idivl %%ecx;"         /* eax = (D - B) / (C + A) */
        
        "movl %1, %%ebx;" 		/* ebx = D */ 
        "imull %%ebx;"  		/* eax = (D - B) / (C + A) * D */
        
        "movl %4, %%ecx;"      /* ecx = A */
        "subl %%ecx, %%eax;"   /* eax = (D - ?? / (C + A) * D - A */

        "movl %5, %%ebx;"      /* ebx = E */
        "addl %%ebx, %%eax;"   /* eax = (D - ?? / (C + A) * D - A + E */
    
        "movl %6, %%ebx;"      /* ebx = F */
        "subl %%ebx, %%eax;"   /* eax = (D - ?? / (C + A) * D - A + E - F */ 

        "movl %%eax, %0;"  
        : "=r" (res2)        
        : "r" (D), "r" (B), "r" (C), "r" (A), "r" (E), "r" (F)
        : "%eax", "%ebx", "%ecx", "%edx"  
    );
    
	printf("The result of the calculation with assembler inserts: (%d - %d)/ (%d + %d) * %d - %d + %d - %d = %d\n", D, B, C, A, D, A, E, F, res2);

    return 0;
}
