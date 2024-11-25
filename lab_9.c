/*
В каждом варианте задания необходимо создать программу, принимающую в качестве параметров запуска первым аргументом текст для обработки, вторым аргументом - 
команду обработки (одну из трёх), и после нее необходимые для работы команды дополнительные аргументы. Все команды обработки делятся на три вида: информация, 
создание, удаление (заданы ниже по-вариантно).  Таким образом запуск программы должен иметь следующий формат: 
Lab6.exe "Текст для обработки идёт первым аргументом." -info 5 Где второй аргумент задаёт команду, соответственно: -info для команды «информация». -create для команды «создание». -delete для команды «удаление». 
Третьим и далее аргументами идёт необходимый набор параметров для каждой из этих команд. В каждом варианте задания требуется создать минимум три функции 
реализующие соответствующие команды. При применении команды «информация» в консоль следует вывести искомое количество, при «создании» вывести созданный массив 
в консоль, а при «удалении» вывести в консоль модифицированный текст. При любом сравнении последовательностей не учитывать регистр букв. В команде «создание» 
использовать динамические массивы. Весь текстовый вывод в консоль должен осуществляться исключительно из основной функции main. Программа также должна 
правильно обрабатывать случай, когда аргументы запуска отсутствуют либо заданы неверно, и выводить текст ошибки, поясняющий что конкретно было сделано 
неправильно при задании параметров. 

Важно: любой текст может состоять из слов, чисел, либо иных последовательностей 
символов. Также текст может быть разбит знаками препинания на предложения. 
Слово – последовательность символов, состоящая только из букв верхнего или нижнего 
регистра. 
Число – последовательность символов, состоящая из цифр 0…9. Числа считаются только 
целыми.

Информация: Функция, возвращающая максимальную длину слова, встречающуюся в тексте. 
Создание: Функция, создающая массив слов, длинней K-букв.
Удаление: Функция, удаляющая из текста все иные последовательности, не являющиеся ни словами, ни числами.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1 Max word lenght
int mx_word(const char *text)
{
	int mx = 0, cur = 0;
	int i = 0;
	for (i = 0; i < text[i] != '\0'; i++)
	{
		if (isalpha(text[i]))
		{
			cur++;
		}
		else
		{
			if (cur > mx)
			{
				mx = cur;
			}
			cur = 0;
		}
	}
	if (cur > mx)
	{
		mx = cur;
	}
	return mx;
}
// 2 array words len = k
char **words_len_k(const char *text, int k, int *count)
{
	char **words = NULL;
	int i = 0;
	int j = 0;
	const char *start = NULL;
	do {
        if (isalpha(text[i])) 
		{ 
            if (!start) 
			{
                start = &text[i]; 
            }
        } 
		else 
		{
            if (start) 
			{
                int word_len = &text[i] - start;
                if (word_len == k) 
				{ 
                    char **temp = realloc(words, (*count + 1) * sizeof(char *));
                    if (!temp) 
					{
                        printf("Memory allocation error\n");
                        for (j = 0; j < *count; j++) {
                            free(words[j]);
                        }
                        free(words);
                        exit(1);
                    }
                    words = temp;

    
                    words[*count] = (char *)malloc((word_len + 1) * sizeof(char));
                    if (!words[*count]) 
					{
                        printf("Memory allocation error\n");
                        for (j = 0; j < *count; j++) {
                            free(words[j]);
                        }
                        free(words);
                        exit(1);
                    }
                    strncpy(words[*count], start, word_len);
                    words[*count][word_len] = '\0';
                    (*count)++;
                }
                start = NULL; 
            }
        }
        i++;
    } while (text[i - 1] != '\0'); 

    return words;
}

// 3 delete non words and numbers
char *delete_text(const char *text)
{
	int len = strlen(text);
    char *result = (char *)malloc(len + 1);  

    if (!result) {
        printf("Memory allocation error\n");
        exit(1);
    }

    char *write_ptr = result;  
    const char *read_ptr = text;  

    while (*read_ptr) 
	{
        if (isalpha((unsigned char)*read_ptr) || isdigit((unsigned char)*read_ptr)) 
		{
            *write_ptr++ = *read_ptr;
        } 
		else if (*read_ptr == ' ' || *read_ptr == ',' || *read_ptr == '.' || *read_ptr == '!' || *read_ptr == '?') 
			{
            	if (write_ptr != result && *(write_ptr - 1) != ' ') 
				{
                	*write_ptr++ = ' ';  
            	}
        	}
        read_ptr++;
    }

    
    if (write_ptr != result && *(write_ptr - 1) == ' ') {
        write_ptr--;
    }

    *write_ptr = '\0'; 

    return result;  
}

int main(int argc, char **argv) {
	if (argc < 3) 
	{
        printf("Usage: program \"text\" -command [arguments]\n");
        return 1;
    }

    char *text = argv[1];
    char *command = argv[2];
	printf("Your text: \n");
	puts(text);
	
	if (strcmp(command, "-info") == 0)
	{
		if (argc != 3){
			printf("Error: -info does not require additional arguments\n");
            return 1;
		}
		int max_len = mx_word(text);
		printf("Max word length: %d\n", max_len);
	}
	
	else if(strcmp(command, "-create") == 0)
	{
		if (argc != 4)
		{
			printf("Error: -create requires a numeric argument K\n");
            return 1;
		}
		int k = atoi(argv[3]);
		
		if (k <= 0) 
		{
            printf("Error: K must be a positive number\n");
            return 1;
        }
        int count = 0;
        char **words_k = words_len_k(text, k, &count);
        printf("Words len wored %d:\n", k);
        int i = 0;
        for (i = 0; i < count; i++)
		{
			printf("%s\n", words_k[i]);
			free(words_k[i]);
		}
		free(words_k);   
	}
	else if(strcmp(command, "-delete") == 0)
	{
		if (argc != 3)
		{
			printf("Error: -delete does not require additional arguments\n");
            return 1;
		}
		char *text_copy = delete_text(text);
		printf("Text after deletion:\n%s\n", text_copy);
		free(text_copy);
	}
	else
	{
		printf("Error: Unknown command %s\n", command);
        return 1;
	}
	return 0;
}
