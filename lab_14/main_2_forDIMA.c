#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>

#define point_type double
#define absolute_value(a) fabs(a)
#define string_type "%lf"
#define MAX_FILENAME_LEN 20

// Структура прямоугольника
typedef struct {
    point_type x1, y1;
    point_type x2, y2;
    bool square;
} Rectangle;

// Структура для записи операций
typedef struct {
    int operation;              // Код выполненной операции
    Rectangle rect;             // Прямоугольник, к которому применена операция
    point_type params[4];       // Параметры операции
    point_type result[2];       // Результаты операции (например, площадь и периметр)
} OperationRecord;

// Функции для работы с прямоугольниками
Rectangle Create_rectangle(point_type x1, point_type y1, point_type x2, point_type y2) {
    Rectangle rect;
    rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    rect.square = (absolute_value(x2 - x1) == absolute_value(y2 - y1));
    return rect;
}

void move_rectangle(Rectangle *rect, point_type dx, point_type dy) {
    rect->x1 += dx;
    rect->x2 += dx;
    rect->y1 += dy;
    rect->y2 += dy;
}

void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h) {
    rect->x2 = rect->x1 + new_w;
    rect->y2 = rect->y1 - new_h;
    rect->square = (absolute_value(new_w) == absolute_value(new_h));
}

void calculate(Rectangle *rect, point_type *area, point_type *perimeter) {
    point_type w = absolute_value(rect->x2 - rect->x1);
    point_type h = absolute_value(rect->y1 - rect->y2);
    *area = w * h;
    *perimeter = 2 * (w + h);
}

// Меню выбора операции
void choose_menu() {
    printf("1. Создать прямоугольник\n");
    printf("2. Переместить прямоугольник\n");
    printf("3. Изменить размеры прямоугольника\n");
    printf("4. Вычислить площадь и периметр\n");
    printf("5. Выход\n");
}

// Запись данных в файл
void writeFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    int choice;
    Rectangle rect;
    point_type params[4];

    choose_menu();

    while (true) {
        printf("Выберите действие: ");
        scanf("%d", &choice);

        if (choice == 5) {
            break;
        }

        OperationRecord record = {0};
        record.operation = choice;

        switch (choice) {
            case 1: // Создание прямоугольника
                printf("Введите координаты x1, y1, x2, y2: ");
                scanf(string_type string_type string_type string_type, &params[0], &params[1], &params[2], &params[3]);
                record.rect = Create_rectangle(params[0], params[1], params[2], params[3]);
                break;

            case 2: // Перемещение
                printf("Введите смещения dx и dy: ");
                scanf(string_type string_type, &params[0], &params[1]);
                move_rectangle(&record.rect, params[0], params[1]);
                break;

            case 3: // Изменение размеров
                printf("Введите новую ширину и высоту: ");
                scanf(string_type string_type, &params[0], &params[1]);
                change_rectangle(&record.rect, params[0], params[1]);
                break;

            case 4: // Вычисление площади и периметра
                calculate(&record.rect, &record.result[0], &record.result[1]);
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                continue;
        }

        fwrite(&record, sizeof(OperationRecord), 1, file);
    }

    fclose(file);
    printf("Данные успешно записаны в файл.\n");
}

// Обработка данных из файла
void processFile(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");

    if (!input_file || !output_file) {
        printf("Ошибка открытия файлов для обработки.\n");
        return;
    }

    OperationRecord record;
    while (fread(&record, sizeof(OperationRecord), 1, input_file)) {
        switch (record.operation) {
            case 4: // Вычисление площади и периметра
                calculate(&record.rect, &record.result[0], &record.result[1]);
                break;

            default:
                break;
        }
        fwrite(&record, sizeof(OperationRecord), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    printf("Обработка данных завершена.\n");
}

// Чтение результатов из файла
void readResults(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Ошибка открытия файла для чтения.\n");
        return;
    }

    OperationRecord record;
    while (fread(&record, sizeof(OperationRecord), 1, file)) {
        printf("\nОперация: %d\n", record.operation);
        printf("Прямоугольник:\n");
        printf("(%.2f, %.2f)  (%.2f, %.2f)\n", record.rect.x1, record.rect.y1, record.rect.x2, record.rect.y1);
        printf("(%.2f, %.2f)  (%.2f, %.2f)\n", record.rect.x1, record.rect.y2, record.rect.x2, record.rect.y2);
        if (record.operation == 4) {
            printf("Площадь: %.2f, Периметр: %.2f\n", record.result[0], record.result[1]);
        }
    }

    fclose(file);
}

// Главная функция
int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
    int mode;
    char input_filename[MAX_FILENAME_LEN], output_filename[MAX_FILENAME_LEN];

    while (true) {
        printf("\nВыберите режим работы:\n");
        printf("1. Запись данных\n");
        printf("2. Обработка данных\n");
        printf("3. Чтение результатов\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                printf("Введите имя файла для записи данных: ");
                scanf("%s", input_filename);
                writeFile(input_filename);
                break;

            case 2:
                printf("Введите имя входного файла: ");
                scanf("%s", input_filename);
                printf("Введите имя выходного файла: ");
                scanf("%s", output_filename);
                processFile(input_filename, output_filename);
                break;

            case 3:
                printf("Введите имя файла для чтения результатов: ");
                scanf("%s", output_filename);
                readResults(output_filename);
                break;

            case 0:
                printf("Выход из программы.\n");
                return 0;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
