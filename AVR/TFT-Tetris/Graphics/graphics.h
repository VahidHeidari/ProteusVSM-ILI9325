#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "tft-ili9325.h"

#define SCREEN_WIDTH		240
#define SCREEN_HEIGHT		320

#define	BLACK	0x0000
#define	BLUE	0x001F
#define	GREEN 	0x07E0
#define CYAN	0x07FF
#define	RED 	0xF800
#define MAGENTA 0xF81F
#define PURPLE	0xF81F
#define YELLOW	0xFFE0
#define WHITE	0xFFFF

#define RGB(r, g, b)	(((r << 10) & RED) \
					  | ((g << 5) & GREEN) \
					  | (b & BLUE))

#define SWAP(a, b, tmp)		tmp = a;	\
							a = b;		\
                            b = tmp;

typedef unsigned int color;

typedef struct point_tag
{
	int x;
    int y;
}point, * pPoint;

typedef struct line_tag
{
	point start;
    point end;
}line, *pLine;

typedef struct rectangle_tag
{
	point p;
    int width;
    int height;
}rectangle, * pRectangle;

#pragma used+

/**
 * Add two point.
 *
 * @param a The left point to add.
 * @param b The right point to add.
 * @return The result of addition of a and b.
 */
point add_point(pPoint a, pPoint b);

/**
 * Set the pixel by the given point.
 *
 * @param p The point to set color.
 * @param c The color of pixel to set.
 */
void set_pixel(point p, color c);

/**
 * Drow a vertical line.
 *
 * @param p1 Starting point of the line.
 * @param p2 Ending point ot the line.
 * @param c Color to draw.
 */
void draw_vertical_line(point p1, point p2, color c);

/**
 * Draw a horizontal line.
 *
 * @param p1 Starting point of the line.
 * @param p2 End point of the line.
 * @parma c Color to draw.
 */
void draw_horizontal_line(point p1, point p2, color c);

/**
 * Draw a line.
 *
 * @param p1 Starting point of the line.
 * @param p2 Ending point of the line.
 */
void draw_line(point p1, point p2, color c);

/**
 * Draw a rectangle.
 *
 * @param rect The rectangle you want to draw.
 * @param c Color to draw.
 */
void draw_rectangle(rectangle rect, color c);

void fill_rectangle(rectangle rect, color c);

void plot_8_circle_point(pPoint center, point p, color c);

/**
 * Draw a circle.
 *
 * @param center The center of circle.
 * @param radius The radius of circle.
 * @param c Color to draw.
 */
void draw_circle(point center, unsigned int radius, color c);

void fill_circle(point center, unsigned int radius, color c);

/**
 * Fill screen by given color.
 *
 * @param c The color of screen.
 */
void clear_screen(color c);

void draw_char(char ch, const pPoint p, const pPoint s, color c);

void draw_string(char* str, point p, point scale, color c);

void draw_stringf(flash char* str, point p, point scale, color c);

#pragma used-

#endif
