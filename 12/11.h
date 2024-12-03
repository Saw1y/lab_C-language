#ifndef LAB11_H
#define LAB11_H
#define point_type double 
#define absolute_value(a) fabs(a)
#define string_type "%lf"

typedef struct  
{
	point_type x1, y1; 
	point_type x2, y2; 
	bool square;   
} Rectangle;

Rectangle Create_rectangle(point_type x1, point_type y1, point_type x2, point_type y2);
void move_rectangle(Rectangle *rect, point_type dx, point_type dy);
void calculate(Rectangle *rect, point_type *area, point_type *perimeter);
Rectangle min_rectangle(point_type points[][2], int size);
Rectangle intersection_rectangles(Rectangle rect1, Rectangle rect2);
Rectangle inscribed_circle(point_type x, point_type y, point_type r);
void change_rectangle(Rectangle *rect, point_type new_w, point_type new_h);


#endif



