#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>

#define point_type double 
#define absolute_value(a) fabs(a)
#define string_type "%lf"

typedef struct  
{
	point_type x1, y1; 
	point_type x2, y2; 
	bool square;   
} Rectangle;

// 1. Создание структуры 
Rectangle Create_rectangle(point_type x1, point_type y1, point_type x2, point_type y2)
{
	Rectangle rect;
	rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    rect.square = (absolute_value(x2 - x1) == absolute_value(y2 - y1)); 
    return rect;
}

// 2. Переместить прямоугольник по X и Y
void move_rectangle(Rectangle *rect, point_type dx, point_type dy)
{
	rect->x1 += dx; 
	rect->x2 += dx; 
	rect->y1 += dy; 
	rect->y2 += dy; 
}

// 3. Изменить ширину и высоту 
void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h)
{
	rect->x2 = rect->x1 + new_w; 
	rect->y2 = rect->y1 - new_h; 
	rect->square = (absolute_value(new_w) == absolute_value(new_h)); 
}

// 4. Вычислить площадь и периметр
void calculate(Rectangle *rect, point_type *area, point_type *perimeter)
{
	point_type w = absolute_value((rect->x2) - (rect->x1)); 
    point_type h = absolute_value((rect->y1) - (rect->y2)); 
    *area = w * h; 
    *perimeter = 2 * (w + h); 
}

// 5. Найти минимальный прямоугольник, содержащий все точки
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

// 6. Найти пересечение двух прямоугольников
Rectangle intersection_rectangles(Rectangle rect1, Rectangle rect2)
{
	point_type x1, y1;
	point_type x2, y2;
	x1 = rect1.x1 > rect2.x1 ? rect1.x1 : rect2.x1;
	y1 = rect1.y1 > rect2.y1 ? rect1.y1 : rect2.y1;
	
	x2 = rect1.x2 < rect2.x2 ? rect1.x2 : rect2.x2;
	y2 = rect1.y2 < rect2.y2 ? rect1.y2 : rect2.y2;
	
	if (x1 > x2 || y1 < y2) {
		Rectangle new_rectangle = Create_rectangle(0, 0, 0, 0); // 
        return new_rectangle;
    }
	Rectangle new_rectangle = Create_rectangle(x1, y1, x2, y2);
    return new_rectangle;
}

// 7. Прямоугольник, вписанный в окружность
Rectangle inscribed_circle(point_type x, point_type y, point_type r)
{
	point_type side = r * sqrt(2); 
	Rectangle new_rectangle = Create_rectangle(x - side / 2, y + side / 2, x + side / 2, y - side / 2);
	return new_rectangle;
} 

// 8. Вывод
void print_rectangle(Rectangle rect)
{
	printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y1, rect.x2, rect.y1);
    printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y2, rect.x2, rect.y2);
    printf("[%s]\n", rect.square ? "Квадрат" : "Прямоугольник");
}

// Меню 
void choose_menu(int *choose)
{
	printf("1. Создать структуру\n");
	printf("2. Переместить прямоугольник по X и Y\n");
	printf("3. Изменить ширину и высоту\n");
	printf("4. Вычислить площадь и периметр\n");
	printf("5. Найти минимальный прямоугольник, содержащий все точки\n");
	printf("6. Найти пересечение двух прямоугольников\n");
	printf("7. Найти прямоугольник, вписанный в окружность\n");
	printf("8. Вывести прямоугольник\n");
    printf("9. Выход\n");
	printf("Выберите действие: ");
	scanf("%d", choose);
}

int main() {
	int choose;
	Rectangle rectangle = Create_rectangle(0, 0, 0, 0);
    do {
        do {
            choose_menu(&choose);
        } while (choose < 1 || choose > 9);
        
        if (choose == 1) {
            point_type x1, y1, x2, y2;
            printf("Введите первую точку (x, y):\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Введите вторую точку (x, y):\n");
            scanf(string_type " " string_type, &x2, &y2);
            rectangle = Create_rectangle(x1, y1, x2, y2);
            print_rectangle(rectangle);
        }
        else if (choose == 2) {
            point_type dx, dy;
            printf("Введите смещение по X:\n");
            scanf(string_type, &dx);
            printf("Введите смещение по Y:\n");
            scanf(string_type, &dy);
            move_rectangle(&rectangle, dx, dy);
            print_rectangle(rectangle);
        }
        else if (choose == 3) {
            point_type newWidth, newHeight;
            printf("Введите новую ширину:\n");
            scanf(string_type, &newWidth);
            printf("Введите новую высоту:\n");
            scanf(string_type, &newHeight);
            change_rectangle(&rectangle, newWidth, newHeight);
            print_rectangle(rectangle);
        }
        else if (choose == 4) {
            point_type a = 0; 
            point_type p = 0;
            calculate(&rectangle, &a, &p);
            print_rectangle(rectangle);
            printf("Площадь = ");
            printf(string_type "\n", a);
            printf("Периметр = ");
            printf(string_type "\n", p);
        }
        else if (choose == 5) {
            Rectangle new_rectangle;
            int count = 0;
            int i;
            point_type x = 0;
            point_type y = 0;
            do {
                printf("Введите количество точек: ");
                scanf("%d", &count);
            } while (count <= 0);

            point_type array[count][2];
            for (i = 0; i < count; i++) {
                printf("Введите координаты точки %d (x, y):\n", i + 1);
                scanf(string_type " " string_type, &x, &y);
                array[i][0] = x;
                array[i][1] = y;
            }
            rectangle = min_rectangle(array, count);
            print_rectangle(rectangle);
        }
        else if (choose == 6) {
            point_type x1, y1, x2, y2;
            point_type x3, y3, x4, y4;
            Rectangle rect1, rect2;
            printf("Введите первую точку первого прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Введите вторую точку первого прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x2, &y2);
            rect1 = Create_rectangle(x1, y1, x2, y2);

            printf("Введите первую точку второго прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x3, &y3);
            printf("Введите вторую точку второго прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x4, &y4);
            rect2 = Create_rectangle(x3, y3, x4, y4);

            rectangle = intersection_rectangles(rect1, rect2);
            print_rectangle(rectangle);		
        }
        else if (choose == 7) {
            point_type x, y, r;
            printf("Введите координаты центра окружности (x, y):\n");
            scanf(string_type " " string_type, &x, &y);
            printf("Введите радиус:\n");
            scanf(string_type, &r);
            rectangle = inscribed_circle(x, y, r);
            print_rectangle(rectangle);
        }
        else if (choose == 8) {
            print_rectangle(rectangle);
        }
    } while (choose != 9);
    
	return 0;
}
