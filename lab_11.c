// Вариант 18. «Прямоугольник» – Rectangle.  
// Разработать структуру данных Rectangle, представляющую фигуру выровненного по осям 
// прямоугольника, заданный двумя координатами: соответственно верхней левой и 
// нижней правой вершины, а также логическим значением square, показывающим является 
// ли данный прямоугольник квадратом. Должны быть следующие функции:  
// 1) Создание структуры прямоугольника по координатам его двух вершин. Как результат 
// возвращается новый прямоугольник. 
// 2) Перемещение переданного прямоугольника на заданное смещение по оси X и Y. 
// 3) Изменение ширины и высоты для переданного прямоугольника. 
// 4) Вычисление пары значений – площади и периметра – для переданного 
// прямоугольника.  
// 5) Нахождение прямоугольника минимальной площади, внутрь которого попадают все 
// точки, переданные в качестве массива. Как результат возвращается новый 
// прямоугольник. 
// 6) Нахождение прямоугольника, как пересечение двух других переданных 
// прямоугольников. Как результат возвращается новый прямоугольник. 
// 7) Нахождение прямоугольника, вписанного в заданную окружность с координатами 
// центра x,y и радиусом R. Как результат возвращается новый прямоугольник. 
// 8) Вывод в консоль переданного прямоугольника в виде: 
// (0, 5)  (10.5, 5) 
// (0,0)   (10.5,0) 
// [square] 
// где square имеет значение либо «квадрат», либо «прямоугольник». 

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

// 1. Create structure 
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

// 2. Move rectangle in the X and Y
void move_rectangle(Rectangle *rect, point_type dx, point_type dy)
{
	rect->x1 += dx; 
	rect->x2 += dx; 
	rect->y1 += dy; 
	rect->y2 += dy; 
}

// 3. Change the width and height 
void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h)
{
	rect->x2 = rect->x1 + new_w; 
	rect->y2 = rect->y1 - new_h; 
	rect->square = (absolute_value(new_w) == absolute_value(new_h)); 
}

// 4. Calculate area and perimeter
void calculate(Rectangle *rect, point_type *area, point_type *perimeter)
{
	point_type w = absolute_value((rect->x2) - (rect->x1)); 
    point_type h = absolute_value((rect->y1) - (rect->y2)); 
    *area = w * h; 
    *perimeter = 2 * (w + h); 
}

// 5. Finde the minimum area rectangle with all points inside it.
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

// 6. Finde a rectangle as the intersection of two rectangles.
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

// 7. Finde a rectangle inscribed in a given circle with coordinates center x,y and radius R.
Rectangle inscribed_circle(point_type x, point_type y, point_type r)
{
	point_type side = r * sqrt(2); 
	Rectangle new_rectangle = Create_rectangle(x - side / 2, y + side / 2, x + side / 2, y - side / 2);
	return new_rectangle;
} 

// 8. Output
void print_rectangle(Rectangle rect)
{
	printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y1, rect.x2, rect.y1);
    printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y2, rect.x2, rect.y2);
    printf("[%s]\n", rect.square ? "Square" : "Rectangle");
}

// MENU 
void choose_menu(int *choose)
{
	printf("1. Create structure  \n");
	printf("2. Move rectangle in the X and Y \n");
	printf("3. Change the width and height \n");
	printf("4. Calculate area and perimeter \n");
	printf("5. Finde the minimum area rectangle with all points inside it \n");
	printf("6. Finde a rectangle as the intersection of two rectangles \n");
	printf("7. Finde a rectangle inscribed in a given circle with coordinates center x,y and radius R \n");
	printf("8. Output \n");
    printf("9. Exit \n");
	printf("Choose: ");
	scanf("%d", choose);
}

int main() {
	int choose;
	Rectangle rectangle = Create_rectangle(0, 0, 0, 0);
    do{
        do
        {
        choose_menu(&choose);
        }while(choose < 1 || choose > 9);
        
        if (choose == 1)
        {
            point_type x1, y1, x2, y2;
            printf("Enter point1(x, y)\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Enter point2 (x, y)\n");
            scanf(string_type " " string_type, &x2, &y2);
            rectangle = Create_rectangle(x1, y1, x2, y2);
            print_rectangle(rectangle);
        }
        else if (choose == 2)
        {
            point_type dx, dy;
            printf("Enter dx\n");
            scanf(string_type " ", &dx);
            printf("Enter dy\n");
            scanf(string_type " ", &dy);
            move_rectangle(&rectangle, dx, dy);
            print_rectangle(rectangle);
        }
        else if (choose == 3)
        {
            point_type newWidth, newHeight;
            printf("Enter new width\n");
            scanf(string_type " ", &newWidth);
            printf("Enter new height\n");
            scanf(string_type " ", &newHeight);
            change_rectangle(&rectangle, newWidth, newHeight);
            print_rectangle(rectangle);
        }
        else if (choose == 4)
        {
            point_type a = 0; 
            point_type p = 0;
            calculate(&rectangle, &a, &p);
            print_rectangle(rectangle);
            printf("Area = ");
            printf(string_type " ", a);
            printf("\n");
            printf("Petimer = ");
            printf(string_type " ", p);
            
        }
        else if (choose == 5)
        {
            Rectangle new_rectangle;
            int count = 0;
            int i;
            point_type x = 0;
            point_type y = 0;
            do{
            printf("Enter size array: ");
            scanf("%d", &count);
            }while(count < 0);
            point_type array[count][2];
            for (i = 0; i < count; i++)
            {
                printf("Enter point (x, y) %d", i);
                scanf(string_type " " string_type, &x, &y);
                array[i][0] = x;
                array[i][1] = y;
            }
            rectangle =  min_rectangle(array, count);
            print_rectangle(rectangle);

        }
        else if (choose == 6)
        {
            point_type x1, y1, x2, y2;
            point_type x3, y3, x4, y4;
            Rectangle rect1, rect2;
            Rectangle rectangle;
            printf("Enter point1(x, y)\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Enter point2 (x, y)\n");
            scanf(string_type " " string_type, &x2, &y2);
            rect1 = Create_rectangle(x1, y1, x2, y2);

            printf("Enter point1(x, y)\n");
            scanf(string_type " " string_type, &x3, &y3);
            printf("Enter point2 (x, y)\n");
            scanf(string_type " " string_type, &x4, &y4);
            rect2 = Create_rectangle(x3, y3, x4, y4);
            rectangle = intersection_rectangles(rect1, rect2);
            print_rectangle(rectangle);		
        }
        else if (choose == 7)
        {
            Rectangle rectangle;
            point_type x, y, r;
            printf("Enter x: ");
            scanf(string_type " ", &x);
            printf("Enter y: ");
            scanf(string_type " ", &y);
            printf("Enter rad: ");
            scanf(string_type " ", &r);
            rectangle  = inscribed_circle(x, y, r);
            print_rectangle(rectangle);
        }
        else if (choose == 8)
        {
            print_rectangle(rectangle);
        }
    }while (choose != 9);
    
	return 0;
}
