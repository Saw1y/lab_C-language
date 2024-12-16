#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

#define MAX_SENTENCE_LEN 1024
#define MAX_WORD_LEN 256
#define MAX_COMMAND_LEN 64

typedef struct
{
    char text[MAX_SENTENCE_LEN];
    char command[MAX_COMMAND_LEN];
    char param[MAX_WORD_LEN];
} ParsedLine;

int parseLine(const char *line, ParsedLine *parsed)
{
    strcpy(parsed->param, "");
    int result = sscanf(line, "\"%[^\"]\" -%s %s", parsed->text, parsed->command, parsed->param);

    if (result < 2)
    {
        return -1;
    }

    return 0;
}
int info(const char *text)
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

char **create(const char *text, int k, int *count)
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
                if (word_len >= k) 
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


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Ошибка: недостаточно аргументов.\n");
        printf("Формат: main.exe \"входной файл\" \"выходной файл\"\n");
        return 1;
    }

    char *input = argv[1];
    char *output = argv[2];

    FILE *inputFile = fopen(input, "r");
    FILE *outputFile = fopen(output, "w");

    if (!inputFile || !outputFile) {
        printf("Ошибка открытия файлов.\n");
        if (inputFile) fclose(inputFile);
        if (outputFile) fclose(outputFile);
        return 1;
    }

    char line[MAX_SENTENCE_LEN];
    ParsedLine parsed;
    
    while (fgets(line, sizeof(line), inputFile)) {
        line[strcspn(line, "\n")] = 0; // Убираем символ новой строки
        if (parseLine(line, &parsed) == 0) {
            if (strcmp(parsed.command, "info") == 0) {
                int middle = info(parsed.text);
                fprintf(outputFile, "%d\n", middle);
            } else if (strcmp(parsed.command, "create") == 0) {
                if (parsed.param[0] == '\0') {
                    printf("Ошибка: команда -create требует параметра.\n");
                    continue;
                }
                int k = atoi(parsed.param);
                if (k <= 0) {
                    printf("Ошибка: параметр k должен быть больше 0.\n");
                    continue;
                }
                int count = 0;
                char **result = create(parsed.text, k, &count);
                if (!result) {
                    printf("Ошибка: не удалось выделить память для слов.\n");
                    continue;
                }
                int i;
                for (i = 0; i < count; i++) {
                    fprintf(outputFile, "%s ", result[i]);
                    free(result[i]);
                }
                fprintf(outputFile, "\n");
                free(result);
            } else if (strcmp(parsed.command, "delete") == 0) {
                char *result = delete_text(parsed.text);
                if (result) {
                    fprintf(outputFile, "%s\n", result);
                    free(result);
                }
            } else {
                printf("Ошибка: неизвестная команда %s.\n", parsed.command);
            }
        } else {
            printf("Ошибка разбора строки: %s\n", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
