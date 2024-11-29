#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define point_type double 
#define absolute_value(a) fabs(a)
typedef struct  
{
	point_type x1, y1;
	point_type x2, y2;
	bool square;
	
} Rectangle;

// 1 Create 
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


// 2 Moving
void move_rectangle(Rectangle *rect, point_type dx, point_type dy)
{
	rect->x1 += dx;
	rect->x2 += dx;
	rect->y1 += dy;
	rect->y2 += dy;
}


// 3 Changing Height and Elevation
void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h)
{
	rect->x2 = rect->x1 + new_w;
	rect->y2 = rect->y1 - new_h;
	rect->square = (absolute_value(new_w) == absolute_value(new_h));
}

// 4 Ñalculate area and perimeter 
void calculate(Rectangle *rect, point_type *area, point_type *perimeter)
{
	point_type w = absolute_value((rect->x2) - (rect->x1));
    point_type h = absolute_value((rect->y1) - (rect->y2));
    *area = w * h;
    *perimeter = 2 * (w + h);
}


// 5 find min area and create new rectangle 
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

// 6 Intersection of two rectangles
Rectangle intersection_rectangles(Rectangle rect1, Rectangle rect2)
{
	point_type x1, y1;
	point_type x2, y2;
	x1 = rect1.x1 > rect2.x1 ? rect1.x1 : rect2.x1;
	y1 = rect1.y1 > rect2.y1 ? rect1.y1 : rect2.y1;
	
	x1 = rect1.x2 > rect2.x2 ? rect1.x2 : rect2.x2;
	y1 = rect1.y2 > rect2.y2 ? rect1.y2 : rect2.y2;
	
	if (x1 > x2 || y1 < y2) {
		Rectangle new_rectangle = Create_rectangle(0, 0, 0, 0);
        return new_rectangle;
    }
	Rectangle new_rectangle = Create_rectangle(x1, y1, x2, y2);
    return new_rectangle;
		
}

// 7 Rectangle inscribed in a circle
Rectangle inscribed_circle(point_type x, point_type y, point_type r)
{
	point_type side = r * sqrt(2);
	Rectangle new_rectangle = Create_rectangle(x - side / 2, y + side / 2, x + side / 2, y - side / 2);
	return new_rectangle;
} 

// 8 Output rectangle 
void print_rectangle(Rectangle rect)
{
	printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y1, rect.x2, rect.y1);
    printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y2, rect.x2, rect.y2);
    printf("[%s]\n", rect.square ? "Square" : "rectangle");
}



int main() {
	return 0;
}
