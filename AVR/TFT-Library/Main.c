#include <stdio.h>

#include "config.h"
#include "graphics.h"
#include "tft-ili9325.h"

char alian[] =
{
    0b00011000,
    0b00111100,
    0b01111110,
    0b11011011,
    0b11111111,
    0b00100100,
    0b01011010,
    0b10100101,
};

void main()
{
    point p1 = {0, 0}, p2 = {SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
    point center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    point text_pos = {SCREEN_WIDTH / 2 - 12 * 6, SCREEN_HEIGHT / 2 - 4 * 8};
    point scale = {2, 2};
    rectangle rect = {10, 10, 50, 10};
    rectangle tetromino = {100, 90, 10, 10};
    int i, j;
    char* str = "Hello, World!";
    char* score = "SCORE : 10520";

    tft_ili9325_init();

    clear_screen(GREEN);

    fill_rectangle(rect, RED);

    draw_line(p1, p2, 0x00ff);

    draw_circle(center, 50, 0xF00F);
    draw_circle(center, 51, 0xf00f);
    draw_circle(center, 52, 0xf00f);
    draw_circle(center, 53, 0xf00f);

    center.x = 20;
    center.y = 100;
    fill_circle(center, 30, WHITE);

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (alian[i] & 0x01 << j)
            {
                p1.x = j * 2;
                p1.y = i * 2;
                set_pixel(p1, 0);
                ++p1.x;
                set_pixel(p1,0);
                ++p1.y;
                set_pixel(p1, 0);
                --p1.x;
                set_pixel(p1, 0);
            }
        }
    }

    draw_string(str, text_pos, scale, 0x0000);
    text_pos.y += 16;
    draw_string(str, text_pos, scale, 0xFF00);
    text_pos.y += 16;
    draw_string(str, text_pos, scale, 0x00FF);
    text_pos.y += 16;
    draw_string(str, text_pos, scale, 0xFA00);

    scale.x = 3;
    scale.y = 4;
    text_pos.y = 20;
    text_pos.x = 10;
    draw_string(score, text_pos, scale, BLACK);

    fill_rectangle(tetromino, BLUE);
    draw_rectangle(tetromino, WHITE);

    while (1)
    {
        continue;
    }
}
