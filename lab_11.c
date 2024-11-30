#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>

#define point_type double 
#define absolute_value(a) fabs(a)
#define string_type "%lf"

// Определение структуры "Прямоугольник"
typedef struct  
{
	point_type x1, y1; // Координаты верхнего левого угла
	point_type x2, y2; // Координаты нижнего правого угла
	bool square;       // Является ли прямоугольник квадратом
} Rectangle;

// 1. Создание прямоугольника
Rectangle Create_rectangle(point_type x1, point_type y1, point_type x2, point_type y2)
{
	Rectangle rect;
	rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    rect.square = (absolute_value(x2 - x1) == absolute_value(y2 - y1)); // Проверка на квадрат
    return rect;
}

// 2. Перемещение прямоугольника
void move_rectangle(Rectangle *rect, point_type dx, point_type dy)
{
	rect->x1 += dx; // Смещение x1
	rect->x2 += dx; // Смещение x2
	rect->y1 += dy; // Смещение y1
	rect->y2 += dy; // Смещение y2
}

// 3. Изменение ширины и высоты прямоугольника
void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h)
{
	rect->x2 = rect->x1 + new_w; // Новая ширина
	rect->y2 = rect->y1 - new_h; // Новая высота
	rect->square = (absolute_value(new_w) == absolute_value(new_h)); // Проверка на квадрат
}

// 4. Вычисление площади и периметра
void calculate(Rectangle *rect, point_type *area, point_type *perimeter)
{
	point_type w = absolute_value((rect->x2) - (rect->x1)); // Ширина
    point_type h = absolute_value((rect->y1) - (rect->y2)); // Высота
    *area = w * h; // Площадь
    *perimeter = 2 * (w + h); // Периметр
}

// 5. Создание минимального прямоугольника, охватывающего заданные точки
Rectangle min_rectangle(point_type points[][2], int size)
{
	point_type minX = points[0][0];
	point_type minY = points[0][1];
    point_type maxX = points[0][0]; 
	point_type maxY = points[0][1];
	int i;
	for (i = 1; i < size; i++)
	{
		if (points[i][0] < minX) minX = points[i][0];
        if (points[i][1] < minY) minY = points[i][1];
        if (points[i][0] > maxX) maxX = points[i][0];
        if (points[i][1] > maxY) maxY = points[i][1];
    }
    Rectangle new_rectangle = Create_rectangle(minX, maxY, maxX, minY);
    return new_rectangle;
}

// 6. Пересечение двух прямоугольников
Rectangle intersection_rectangles(Rectangle rect1, Rectangle rect2)
{
	point_type x1, y1;
	point_type x2, y2;
	x1 = rect1.x1 > rect2.x1 ? rect1.x1 : rect2.x1;
	y1 = rect1.y1 > rect2.y1 ? rect1.y1 : rect2.y1;
	
	x2 = rect1.x2 < rect2.x2 ? rect1.x2 : rect2.x2;
	y2 = rect1.y2 < rect2.y2 ? rect1.y2 : rect2.y2;
	
	if (x1 > x2 || y1 < y2) {
		Rectangle new_rectangle = Create_rectangle(0, 0, 0, 0); // Если пересечения нет
        return new_rectangle;
    }
	Rectangle new_rectangle = Create_rectangle(x1, y1, x2, y2);
    return new_rectangle;
}

// 7. Прямоугольник, вписанный в круг
Rectangle inscribed_circle(point_type x, point_type y, point_type r)
{
	point_type side = r * sqrt(2); // Сторона квадрата
	Rectangle new_rectangle = Create_rectangle(x - side / 2, y + side / 2, x + side / 2, y - side / 2);
	return new_rectangle;
} 

// 8. Вывод прямоугольника на экран
void print_rectangle(Rectangle rect)
{
	printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y1, rect.x2, rect.y1);
    printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y2, rect.x2, rect.y2);
    printf("[%s]\n", rect.square ? "Квадрат" : "Прямоугольник");
}


void choose_menu(int *choose)
{
	printf("1. Создание прямоугольника\n");
	printf("2. Перемещение прямоугольника\n");
	printf("3. Изменение ширины и высоты прямоугольника\n");
	printf("4. Вычисление площади и периметра\n");
	printf("5. Создание минимального прямоугольника, охватывающего заданные точки\n");
	printf("6. Пересечение двух прямоугольников\n");
	printf("7. Прямоугольник, вписанный в круг\n");
	printf("8. Вывод прямоугольника на экран\n");
	printf("Выберите операцию: ");
	scanf("%d", choose);
}

int main() {
	setlocale(LC_ALL, "Russian");
	int choose;
	do
	{
	choose_menu(&choose);
	}while(choose < 1 || choose > 8);
	
	Rectangle rectangle = Create_rectangle(0, 0, 0, 0);
	if (choose == 1)
	{
		point_type x1, y1, x2, y2;
		printf("Введите коориднаты точки1 (x, y)\n");
		scanf(string_type " " string_type, &x1, &y1);
		printf("Введите коориднаты точки2 (x, y)\n");
		scanf(string_type " " string_type, &x2, &y2);
		rectangle = Create_rectangle(x1, y1, x2, y2);
		print_rectangle(rectangle);
	}
	else if (choose == 2)
	{
		;	
	}
	else if (choose == 3)
	{
		;	
	}
	else if (choose == 4)
	{
		;	
	}
	else if (choose == 5)
	{
		;
	}
	else if (choose == 6)
	{
		;
	}
	else if (choose == 7)
	{
		;
	}
	else if (choose == 8)
	{
		;
	}
	
	return 0;
}

