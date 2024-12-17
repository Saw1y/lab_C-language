#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_FILENAME_LEN 128

typedef struct
{
    float x1, y1;
    float x2, y2;
    bool is_square;
} Rectangle;

typedef struct
{
    int operation;
    Rectangle rect1;
    Rectangle rect2;
    float values[3];
    float result[2];
} OperationRecord;

Rectangle createRectangle(float x1, float y1, float x2, float y2)
{
    Rectangle rect;
    rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    rect.is_square = (fabs(x2 - x1) == fabs(y2 - y1));
    return rect;
}

void moveRectangle(Rectangle *rect, float dx, float dy)
{
    rect->x1 += dx;
    rect->y1 += dy;
    rect->x2 += dx;
    rect->y2 += dy;
}

void resizeRectangle(Rectangle *rect, float new_width, float new_height)
{
    rect->x2 = rect->x1 + new_width;
    rect->y2 = rect->y1 - new_height;
    rect->is_square = (fabs(new_width) == fabs(new_height));
}

void calculateAreaAndPerimeter(Rectangle rect, float *area, float *perimeter)
{
    float width = fabs(rect.x2 - rect.x1);
    float height = fabs(rect.y2 - rect.y1);
    *area = width * height;
    *perimeter = 2 * (width + height);
}

Rectangle rectangleInCircle(float cx, float cy, float radius)
{
    float side = radius * sqrt(2);
    return createRectangle(cx - side / 2, cy + side / 2, cx + side / 2, cy - side / 2);
}

Rectangle intersectRectangles(Rectangle rect1, Rectangle rect2)
{
    float x1 = fmax(rect1.x1, rect2.x1);
    float y1 = fmin(rect1.y1, rect2.y1);
    float x2 = fmin(rect1.x2, rect2.x2);
    float y2 = fmax(rect1.y2, rect2.y2);

    if (x1 < x2 && y1 > y2)
    {
        return createRectangle(x1, y1, x2, y2);
    }
    else
    {
        return createRectangle(0, 0, 0, 0);
    }
}

void writeBinaryFile()
{
    char filename[MAX_FILENAME_LEN];
    printf("Введите имя файла для записи данных: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    int choice;
    OperationRecord record;

    printf("\nДоступные операции:\n");
    printf("1. Создать прямоугольник\n");
    printf("2. Переместить прямоугольник\n");
    printf("3. Изменить размеры прямоугольника\n");
    printf("4. Найти пересечение двух прямоугольников\n");
    printf("5. Вычислить площадь и периметр\n");
    printf("6. Найти прямоугольник, вписанный в окружность\n");
    printf("0. Завершить запись\n");

    while (1)
    {
        printf("\nВведите номер операции: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            break;
        }

        record.operation = choice;

        switch (choice)
        {
        case 1:
            printf("Введите координаты верхней левой вершины (x1, y1): ");
            scanf("%f %f", &record.rect1.x1, &record.rect1.y1);
            printf("Введите координаты нижней правой вершины (x2, y2): ");
            scanf("%f %f", &record.rect1.x2, &record.rect1.y2);
            record.rect1.is_square = (fabs(record.rect1.x2 - record.rect1.x1) == fabs(record.rect1.y2 - record.rect1.y1));
            break;

        case 2:
            printf("Введите смещение по X и Y: ");
            scanf("%f %f", &record.values[0], &record.values[1]);
            break;

        case 3:
            printf("Введите новую ширину и высоту: ");
            scanf("%f %f", &record.values[0], &record.values[1]);
            break;

        case 4:
            printf("Введите координаты первого прямоугольника (x1, y1, x2, y2): ");
            scanf("%f %f %f %f", &record.rect1.x1, &record.rect1.y1, &record.rect1.x2, &record.rect1.y2);
            printf("Введите координаты второго прямоугольника (x1, y1, x2, y2): ");
            scanf("%f %f %f %f", &record.rect2.x1, &record.rect2.y1, &record.rect2.x2, &record.rect2.y2);
            break;

        case 5:
            break;
        case 6:
            printf("Введите дополнительные параметры (cx, cy, radius): ");
            scanf("%f %f %f", &record.values[0], &record.values[1], &record.values[2]);
            break;

        default:
            printf("Неверный выбор. Повторите попытку.\n");
            continue;
        }

        fwrite(&record, sizeof(OperationRecord), 1, file);
    }

    fclose(file);
    printf("Данные записаны в файл %s\n", filename);
}

void processBinaryFile()
{
    char inputFile[MAX_FILENAME_LEN], outputFile[MAX_FILENAME_LEN];
    printf("Введите имя файла с данными: ");
    scanf("%s", inputFile);
    printf("Введите имя файла для записи результатов: ");
    scanf("%s", outputFile);

    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");

    if (!in || !out)
    {
        printf("Ошибка открытия файла.\n");
        return;
    }

    OperationRecord record;
    Rectangle currentRectangle = {0, 0, 0, 0, false};
    bool isRectangleInitialized = false;

    while (fread(&record, sizeof(OperationRecord), 1, in) == 1)
    {
        switch (record.operation)
        {
        case 1: 
            currentRectangle = record.rect1;
            isRectangleInitialized = true;
            break;

        case 2: 
            if (isRectangleInitialized)
            {
                moveRectangle(&currentRectangle, record.values[0], record.values[1]);
                record.rect1 = currentRectangle;
            }
            break;

        case 3: 
            if (isRectangleInitialized)
            {
                resizeRectangle(&currentRectangle, record.values[0], record.values[1]);
                record.rect1 = currentRectangle;
            }
            break;

        case 4: 
        {
            Rectangle intersection = intersectRectangles(record.rect1, record.rect2);
            record.rect1 = intersection; 
        }
        break;

        case 5: 
            if (isRectangleInitialized)
            {
                calculateAreaAndPerimeter(currentRectangle, &record.result[0], &record.result[1]);
            }
            break;

        case 6: 
        {
            Rectangle rect = rectangleInCircle(record.values[0], record.values[1], record.values[2]);
            record.rect1 = rect; 
        }
        break;

        default:
            printf("Неизвестная операция: %d\n", record.operation);
        }

        fwrite(&record, sizeof(OperationRecord), 1, out); 
    }

    fclose(in);
    fclose(out);
    printf("Результаты записаны в файл %s\n", outputFile);
}

void readResultsFile()
{
    char filename[MAX_FILENAME_LEN];
    printf("Введите имя файла с результатами: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Ошибка открытия файла.\n");
        return;
    }

    OperationRecord record;

    while (fread(&record, sizeof(OperationRecord), 1, file) == 1)
    {
        printf("\nОперация: %d\n", record.operation);

        switch (record.operation)
        {
        case 1:
            printf("Аргументы: (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            printf("Результат: прямоугольник (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            break;

        case 2:
            printf("Аргументы: смещение по X = %.2f, по Y = %.2f\n",
                   record.values[0], record.values[1]);
            printf("Результат: прямоугольник (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            break;

        case 3:
            printf("Аргументы: новая ширина = %.2f, новая высота = %.2f\n",
                   record.values[0], record.values[1]);
            printf("Результат: прямоугольник (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            break;

        case 4:
            printf("Аргументы: прямоугольники\n");
            printf(" Первый: (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            printf(" Второй: (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect2.x1, record.rect2.y1, record.rect2.x2, record.rect2.y2);
            printf("Результат: прямоугольник (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            break;

        case 5:
            printf("Аргументы: текущий прямоугольник\n");
            printf("Результат: площадь = %.2f, периметр = %.2f\n",
                   record.result[0], record.result[1]);
            break;

        case 6:
            printf("Аргументы: центр окружности (%.2f, %.2f), радиус = %.2f\n",
                   record.values[0], record.values[1], record.values[2]);
            printf("Результат: прямоугольник (%.2f, %.2f) - (%.2f, %.2f)\n",
                   record.rect1.x1, record.rect1.y1, record.rect1.x2, record.rect1.y2);
            break;
        }
    }

    fclose(file);
}

int main()
{
	setlocale(LC_ALL, "Russian");
    int mode;
    while (1)
    {
        printf("\nВыберите режим работы:\n");
        printf("1. Запись данных\n");
        printf("2. Обработка данных\n");
        printf("3. Чтение результатов\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &mode);

        switch (mode)
        {
        case 1:
            writeBinaryFile();
            break;
        case 2:
            processBinaryFile();
            break;
        case 3:
            readResultsFile();
            break;
        case 0:
            printf("Выход из программы.\n");
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
