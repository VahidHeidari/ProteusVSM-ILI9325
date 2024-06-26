#include "graphics.h"
#include "font.h"

point add_point(pPoint a, pPoint b)
{
	point result;

    result.x = a->x + b->x;
    result.y = a->y + b->y;

    return result;
}

void set_pixel(point p, color c)
{
	if (p.x < 0 || p.x >= SCREEN_WIDTH
	|| p.y < 0 || p.y >= SCREEN_HEIGHT)
		return;

	tft_ili9325_wr_cmd(0x20, p.x);	// X
    tft_ili9325_wr_cmd(0x21, p.y);	// Y
	tft_ili9325_wr_reg(0x22);
	tft_ili9325_wr_data(c);
}

/**
 *  In vertical line p1.x == p2.x. Incremente y from start to end.
 *
 *			|	p1 (x1, y1)
 *			|
 *			|
 *			|	p2 (x2, y2)
 */
void draw_vertical_line(point p1, point p2, color c)
{
	if (p1.x != p2.x)
    	return;

    if (p1.y > p2.y)
    {
    	point tmp;
        SWAP(p1, p2, tmp);
    }

    do
    {
    	set_pixel(p1, c);
        p1.y++;
    }while (p1.y <= p2.y);
}

/**
 * In horizontal line p1.y == p2.y. Increment x from start to end.
 *
 *		p1 (x1, y1)			p2 (x2, y2)
 *			--------------------
 */
void draw_horizontal_line(point p1, point p2, color c)
{
	if (p1.y != p2.y)
    	return;

    if (p1.x > p2.x)
    {
    	point tmp;
        SWAP(p1, p2, tmp);
    }

    do
    {
    	set_pixel(p1, c);
        p1.x++;
    } while (p1.x <= p2.x);
}

void draw_line(point p1, point p2, color c)
{
    int err = 0;
    int dx;
    int dy;

	if (p1.x == p2.x)
    {
    	draw_vertical_line(p1, p2, c);
        return;
    }

    if (p1.y == p2.y)
    {
    	draw_horizontal_line(p1, p2, c);
        return;
    }

    // Reverse line where x1 > x2
    if (p1.x > p2.x)
    {
        point tmp;
        SWAP(p1, p2, tmp);
    }

    dx = p2.x - p1.x;
    dy = p2.y - p1.y;

    if (dy > 0)
    {
        if (dy < dx)
        {
            do
            {
                set_pixel(p1, c);
                err += dy;
                if ((2 * err) >= dx)
                {
                    ++p1.y;
                    err -= dx;
                }
            } while (++p1.x <= p2.x);
        }
        else
        {
            do
            {
                set_pixel(p1, c);
                err += dx;
                if ((2 * err) >= dy)
                {
                    ++p1.x;
                    err -= dy;
                }
            } while (++p1.y <= p2.y);
        }
    }
    else
    {
        dy = -dy;
        if (dy < dx)
        {
            do
            {
                set_pixel(p1, c);
                err -= dy;
                if ((2 * err) <= -dx)
                {
                    --p1.y;
                    err += dx;
                }
            } while (++p1.x <= p2.x);
        }
        else
        {
            do
            {
                set_pixel(p1, c);
                err -= dx;
                if ((2 * err) <= -dy)
                {
                    ++p1.x;
                    err += dy;
                }
            } while (--p1.y >= p2.y);
        }
    }

}

void draw_rectangle(rectangle rect, color c)
{
	point end;

    end = rect.p;
    end.x += rect.width;
    draw_horizontal_line(rect.p, end, c);

    end.x = rect.p.x;
    end.y += rect.height;
    draw_vertical_line(rect.p, end, c);

    end.x += rect.width;
    rect.p.x += rect.width;
    draw_vertical_line(rect.p, end, c);

    rect.p = end;
    end.x -= rect.width;
    draw_horizontal_line(end, rect.p, c);
}

void fill_rectangle(rectangle rect, color c)
{
	int x, y;

    x = rect.p.x + rect.width;
    y = rect.p.y + rect.height;

    if (rect.p.x < 0)
    	rect.p.x = 0;
    if (rect.p.x >= SCREEN_WIDTH)
    	rect.p.x = SCREEN_WIDTH - 1;

    if (rect.p.y < 0)
    	rect.p.y = 0;
    if (rect.p.y >= SCREEN_HEIGHT)
    	rect.p.y = SCREEN_HEIGHT - 1;

    if (x >= SCREEN_WIDTH)
    	rect.width = SCREEN_WIDTH - rect.p.x;
    if (y >= SCREEN_HEIGHT)
    	rect.height = SCREEN_HEIGHT - rect.p.y;

	for (y = rect.p.y; y <= rect.height; ++y)
    {
        tft_ili9325_wr_cmd(0x20, rect.p.x);	// X
        tft_ili9325_wr_cmd(0x21, y);	// Y
        tft_ili9325_wr_reg(0x22);

        TFT_ILI9325_WR_DATA_LOW = (unsigned char)c;
        TFT_ILI9325_WR_DATA = (unsigned char)(c >> 8);

        TFT_ILI9325_CS_0;
    	for (x = rect.p.x; x <= rect.width; ++x)
        {
    		TFT_ILI9325_WR_0;
    		TFT_ILI9325_WR_1;
        }
        TFT_ILI9325_CS_1;
    }
}

void plot_8_circle_point(pPoint center, point p, color c)
{
	int tmp;

	set_pixel(add_point(center, &p), c);		// (X, Y)

    p.x = -p.x;
    set_pixel(add_point(center, &p), c);		// (-X, Y)

    p.y = -p.y;
    set_pixel(add_point(center, &p), c);		// (-X, -Y)

    p.x = -p.x;
    set_pixel(add_point(center, &p), c);		// (X, -Y)

    SWAP(p.x, p.y, tmp);
    set_pixel(add_point(center, &p), c);		// (-Y, X)

    p.x = -p.x;
    set_pixel(add_point(center, &p), c);		// (-Y, -X)

    p.y = -p.y;
    set_pixel(add_point(center, &p), c);		// (Y, -X)

    p.x = -p.x;
    set_pixel(add_point(center, &p), c);		// (Y, X)
}

void draw_circle(point center, unsigned int radius, color c)
{
	point p;
    int radius_error;

    p.x = radius;
    p.y = 0;
    radius_error = 1 - p.x;

    while (p.x >= p.y)
    {
    	plot_8_circle_point(&center, p, c);
        ++p.y;
        if (radius_error < 0)
        	radius_error += 2 * p.y + 1;
        else
        {
        	--p.x;
            radius_error += 2 * (p.y - p.x + 1);
        }
    }
}

void fill_circle(point center, unsigned int radius, color c)
{
	point p;

    for (p.y = 0; p.y <= radius; ++p.y)
    	for (p.x = 0; p.x <= radius; ++p.x)
        	if (p.x * p.x + p.y * p.y <= radius * radius)
            {
            	set_pixel(add_point(&p, &center), c);		// (X, Y)

                p.x = -p.x;
                set_pixel(add_point(&p, &center), c);		// (-X, Y)

                p.y = -p.y;
                set_pixel(add_point(&p, &center), c);		// (-X, -Y)

                p.x = -p.x;
                set_pixel(add_point(&p, &center), c);		// (X, -Y)

                p.y = -p.y;		// (X, Y)
            }
}

void clear_screen(color c)
{
	int x, y;

	tft_ili9325_wr_cmd(0x20, 0);	// X
    tft_ili9325_wr_cmd(0x21, 0);	// Y
    tft_ili9325_wr_reg(0x22);

    TFT_ILI9325_CS_0;

    TFT_ILI9325_WR_DATA = (unsigned char)(c >> 8);
    TFT_ILI9325_WR_DATA_LOW = (unsigned char)c;

    for (y = 0; y < SCREEN_HEIGHT; ++y)
    {
    	for (x = 0; x < SCREEN_WIDTH; ++x)
        {
    		TFT_ILI9325_WR_0;
    		TFT_ILI9325_WR_1;
        }
    }

    TFT_ILI9325_CS_1;
}

void draw_char(char ch, const pPoint p, const pPoint s, color c)
{
	char x, y;
    char i, j;
    point pixel;

    for (x = 0; x < FONT_WIDTH; ++x)
    {
    	for (y = 0; y <= FONT_HEIGTH; ++y)
        {
        	if (font[((int)ch - ' ') * FONT_WIDTH + x] & (0x01 << y))
            {
            	pixel.x = p->x + x * s->x;
                pixel.y = p->y + y * s->y;
                for (i = 0; i < s->y; ++i)
                {
                	for (j = 0; j < s->x; ++j)
                    {
                		set_pixel(pixel, c);
                        ++pixel.x;
                    }

                	++pixel.y;
                    pixel.x -= s->x;
                }
            }
        }
    }
}

void draw_string(char* str, point p, point scale, color c)
{
	while (*str)
    {
    	draw_char(*str, &p, &scale, c);
        p.x += (FONT_WIDTH + 1) * scale.x;
        ++str;
    }
}

void draw_stringf(flash char* str, point p, point scale, color c)
{
	while (*str)
    {
    	draw_char(*str, &p, &scale, c);
        p.x += (FONT_WIDTH + 1) * scale.x;
        ++str;
    }
}
