#include "tetris.h"

#include <delay.h>
#include <stdlib.h>

#include "joystick.h"

unsigned int tetris_stack[TETRIS_WIDTH][TETRIS_HEIGHT];
flash char tetris_tetrominos[TETRIS_NUM_TETROMINOS][TETRIS_TETROMINO_HEIGHT + TETRIS_TETROMINO_NUM_FIELDS] =
{
    {           //----------			O
        0b000,
        0b011,          ////
        0b011,          ////

        2,		// WIDTH
        2,		// HEIGHT
    }          //----------

    {          //---------				Z
        0b000,
        0b110,        ////
        0b011,          ////

        3,		// WIDTH
        2,		// HEIGHT
    }
    {
        0b001,           //
        0b011,         ////
        0b010,         //

        2,		// WIDTH
        3,		// HEIGHT
    }         //----------

    {          //---------				S
        0b000,
        0b011,          ////
        0b110,        ////

        3,		// WIDTH
        2,		// HEIGHT
    }
    {
        0b010,         //
        0b011,         ////
        0b001,           //

        2,		// WIDTH
        3,		// HEIGHT
    }         //----------

    {         //----------				I
        0b001,          //
        0b001,          //
        0b001,          //

        1,		// WIDHT
        3,		// HEIGHT
    }
    {
        0b000,
        0b000,       //////
        0b111,

        3,		// WIDTH
        1,		// HEIGHT
    }         //----------

    {         //----------				L
        0b010,        //
        0b010,        //
        0b011,        ////

        2,		// WIDTH
        3,		// HEIGHT
    }
    {
        0b000,
        0b111,      //////
        0b100,      //

        3,		// WIDTH
        2,		// HIGHT
    }
    {
        0b011,       ////
        0b001,         //
        0b001,         //

        2,		// WIDTH
        3,		// HEIGHT
    }
    {
        0b000,          //
        0b001,      //////
        0b111,

        3,		// WIDTH
        2,		// HEIGHT
    }          //----------

    {          //----------				J
        0b01,           //
        0b01,           //
        0b11,         ////

        2,		// WIDTH
        3,		// HEIGHT
    }
    {
        0b000,
        0b100,      //
        0b111,      //////

        3,		// WIDTH
        2,		// HEIGHT
    }
    {
        0b11,        ////
        0b10,        //
        0b10,        //

        2,		// WIDTH
        3,		// HEIGHT
    }
    {
        0b000,
        0b111,     //////
        0b001,         //

        3,		// WIDTH
        2,		// HEIGHT
    }        //----------

};

unsigned int tetris_brik_index;
unsigned int tetris_next_index;
color tetris_brik_color;
color tetris_next_color;
signed int tetris_brik_x;
signed int tetris_brik_y;

signed int tetris_tos;		// Top of stack

unsigned int tetris_score;
TETRIS_BOOL tetris_gameover;

void tetris_run()
{
	point p = {10, 30};
    point s = {2, 2};
    char* str = "Game Over!";

	tetris_init();
	tetris_draw_border();
    tetris_draw_stack();
    tetris_next_brik();
    tetris_draw_brik();
    tetris_draw_score();
    tetris_draw_tos();

	while (!tetris_gameover)
    {
		tetris_get_input();
    	tetris_game_play();
    }

	draw_string(str, p, s, BLACK);
}

void tetris_game_play()
{
	if (!tetris_check_collision())
    {
    	tetris_clear_brik();
    	tetris_move_down();
        tetris_draw_brik();
    }
    else
    {
    	tetris_put_brik();
    	tetris_check_lines();
        if (!tetris_check_gameover())
        	tetris_next_brik();
    }

    delay_ms(200);
}

void tetris_init()
{
	int x, y;

	tetris_brik_index = 0;
    tetris_next_index = 0;
    tetris_next_color = RED;
	tetris_brik_color = RED;
	tetris_brik_x = TETRIS_WIDTH / 2;
    tetris_brik_y = -TETRIS_TETROMINO_HEIGHT;
	tetris_score = 0;
	tetris_gameover = TETRIS_FALSE;
    tetris_tos = TETRIS_HEIGHT;

    for (y = 0; y < TETRIS_HEIGHT; ++y)
    	for (x = 0; x < TETRIS_WIDTH; ++x)
        	tetris_stack[x][y] = TETRIS_BLOCK_FREE_COLOR;

#ifdef DEBUG
	tetris_stack[0][TETRIS_HEIGHT - 1] = RED;
    tetris_stack[2][TETRIS_HEIGHT - 1] = BLUE;
    tetris_stack[3][TETRIS_HEIGHT - 1] = GREEN;
    tetris_stack[4][TETRIS_HEIGHT - 1] = YELLOW;
    tetris_stack[2][TETRIS_HEIGHT - 2] = CYAN;
    tetris_stack[3][TETRIS_HEIGHT - 2] = PURPLE;
    tetris_stack[3][TETRIS_HEIGHT - 3] = BLUE;
    tetris_stack[5][TETRIS_HEIGHT - 3] = PURPLE;
#endif
}

void tetris_draw_stack()
{
	int x, y;
    rectangle block = {0, 0, TETRIS_BLOCK_WIDTH, TETRIS_BLOCK_HEIGHT};
    rectangle stack_r  = {TETRIS_STACK_X, TETRIS_STACK_Y, TETRIS_STACK_WIDTH, TETRIS_STACK_HEIGHT};

	fill_rectangle(stack_r, TETRIS_BACKGROUND_COLOR);
	for (y = 0; y < TETRIS_HEIGHT; ++y)
    {
    	block.p.y = y * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE) + TETRIS_STACK_Y;

    	for (x = 0; x < TETRIS_WIDTH; ++x)
        {
        	if (tetris_stack[x][y] != TETRIS_BLOCK_FREE_COLOR)
            {
        		block.p.x = x * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE) + TETRIS_STACK_X;
        		fill_rectangle(block, tetris_stack[x][y]);
            	draw_rectangle(block, TETRIS_BLOCK_BORDER_COLOR);
            }
        }
    }
}

void tetris_draw_border()
{
    rectangle border_l = {TETRIS_BORDER_LEFT_X, TETRIS_BORDER_SIDE_Y
    						, TETRIS_BORDER_WIDTH, TETRIS_BORDER_HEIGHT};

    rectangle border_r = {TETRIS_BORDER_RIGHT_X, TETRIS_BORDER_SIDE_Y
    						, TETRIS_BORDER_WIDTH, TETRIS_BORDER_HEIGHT};

    rectangle border_b = {TETRIS_BORDER_BOTTOM_X, TETRIS_BORDER_BOTTOM_Y
    						, TETRIS_BORDER_BOTTOM_WIDTH, TETRIS_BORDER_BOTTOM_HEIGHT};

    rectangle next_r 			= {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH - (TETRIS_BLOCK_WIDTH / 2)
    						, TETRIS_BORDER_SIDE_Y + (TETRIS_BORDER_HEIGHT / 2) - (TETRIS_BLOCK_WIDTH / 2)
							, (TETRIS_TETROMINO_WIDTH * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE)) + TETRIS_BLOCK_HEIGHT
                			, (TETRIS_TETROMINO_HEIGHT * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE)) + TETRIS_BLOCK_HEIGHT};

    point next_p = {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH - TETRIS_BLOCK_HEIGHT / 2
    				, TETRIS_BORDER_SIDE_Y + TETRIS_BORDER_HEIGHT / 2 - TETRIS_BLOCK_HEIGHT / 2 - 2 * 8};

    point tos_p = {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH - TETRIS_BLOCK_HEIGHT / 2
    				, TETRIS_BORDER_SIDE_Y + TETRIS_BORDER_HEIGHT / 2 - TETRIS_BLOCK_HEIGHT / 2 - 4 * 8};

    point score_p = {10, 10};
	point next_s = {2, 2};

    char* str_n = "Next";
    char* str_s = "SCORE:";
    char* str_tos = "TOS:";

    fill_rectangle(border_l, TETRIS_BORDER_COLOR);
    fill_rectangle(border_r, TETRIS_BORDER_COLOR);
    fill_rectangle(border_b, TETRIS_BORDER_COLOR);

    fill_rectangle(next_r, TETRIS_BACKGROUND_COLOR);
    draw_rectangle(next_r, TETRIS_BORDER_COLOR);

    draw_string(str_n, next_p, next_s, BLUE);
    draw_string(str_s, score_p, next_s, BLUE);
    draw_string(str_tos, tos_p, next_s, BLUE);
}

void tetris_draw_brik()
{
	int x, y;
    rectangle rect = {0, 0, TETRIS_BLOCK_WIDTH, TETRIS_BLOCK_HEIGHT};

    for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
    	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        	if (tetris_brik_y + y >= 0 && tetris_tetrominos[tetris_brik_index][y] & (0x01 << x))
            {
            	rect.p.x = (tetris_brik_x + x) * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE) + TETRIS_STACK_X;
    			rect.p.y = (tetris_brik_y + y) * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE) + TETRIS_STACK_Y;

                fill_rectangle(rect, tetris_brik_color);
                draw_rectangle(rect, TETRIS_BLOCK_BORDER_COLOR);
            }
}

void tetris_clear_brik()
{
	int x, y;
    rectangle rect = {0, 0, TETRIS_BLOCK_WIDTH, TETRIS_BLOCK_HEIGHT};

    for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
    	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        	if (tetris_brik_y + y >= 0 && tetris_tetrominos[tetris_brik_index][y] & (0x01 << x))
            {
            	rect.p.x = (tetris_brik_x + x) * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE) + TETRIS_STACK_X;
    			rect.p.y = (tetris_brik_y + y) * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE) + TETRIS_STACK_Y;

                fill_rectangle(rect, TETRIS_BACKGROUND_COLOR);
            }
}

void tetris_move_down()
{
	if (tetris_brik_y + TETRIS_TETROMINO_HEIGHT < TETRIS_HEIGHT)
    	++tetris_brik_y;
}

void tetris_move_right()
{
	int x, y;

	if (tetris_brik_x + tetris_brik_width() < TETRIS_WIDTH)
    {
		for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
        	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        		if (tetris_brik_y + y >= 0
                	&& tetris_tetrominos[tetris_brik_index][y] & (0x01 << x)
                	&& tetris_stack[tetris_brik_x + x + 1][tetris_brik_y + y] != TETRIS_BLOCK_FREE_COLOR)
            		return;

    	tetris_clear_brik();
    	++tetris_brik_x;
    	tetris_draw_brik();
    }
}

void tetris_move_left()
{
	int x, y;

	if (tetris_brik_x > 0)
    {
    	for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
        	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        		if (tetris_brik_y + y >= 0
                	&& tetris_tetrominos[tetris_brik_index][y] & (0x01 << x)
                	&& tetris_stack[tetris_brik_x + x - 1][tetris_brik_y + y] != TETRIS_BLOCK_FREE_COLOR)
            		return;

        tetris_clear_brik();
        --tetris_brik_x;
        tetris_draw_brik();
    }
}

void tetris_clear_line(int y)
{
	int x;
    rectangle rect = {TETRIS_STACK_X, 0
    				, TETRIS_BLOCK_WIDTH
                    , TETRIS_BLOCK_HEIGHT};

	rect.p.y = TETRIS_STACK_Y + (y * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE));
    for (x = 0; x < TETRIS_WIDTH; ++x)
    {
    	fill_rectangle(rect, TETRIS_BACKGROUND_COLOR);
    	rect.p.x += TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE;
        delay_ms(50);
    }
}

void tetris_next_brik()
{
	int x, y;
	rectangle rect = {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH
    				, TETRIS_BORDER_SIDE_Y + TETRIS_BORDER_HEIGHT / 2
					, TETRIS_BLOCK_WIDTH
                	, TETRIS_BLOCK_HEIGHT};

	tetris_brik_x = TETRIS_WIDTH / 2;
    tetris_brik_y = -TETRIS_TETROMINO_HEIGHT;

	tetris_brik_index = tetris_next_index;
    tetris_next_index = (tetris_next_index + 1) % TETRIS_NUM_TETROMINOS;

    tetris_brik_color = tetris_next_color;
    tetris_next_color = RED;

    for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
    {
    	for(x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        {
        	if(tetris_tetrominos[tetris_next_index][y] & (0x01 << x))
            {
            	fill_rectangle(rect, tetris_next_color);
                draw_rectangle(rect, TETRIS_BLOCK_BORDER_COLOR);
            }
            else
            	fill_rectangle(rect, TETRIS_BACKGROUND_COLOR);

            rect.p.x += TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE;
        }

        rect.p.y += TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE;
        rect.p.x = TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH;
    }
}

void tetris_check_lines()
{
	int x, y;
    char cleared_lines = 0;

	for (y = TETRIS_HEIGHT - 1; y >= 0; --y)
    {
    	for (x = 0; x < TETRIS_WIDTH; ++x)
        {
        	if (tetris_stack[x][y] == TETRIS_BLOCK_FREE_COLOR)
            	break;
        }

        if (x >= TETRIS_WIDTH)
        {
    		switch (++cleared_lines)
            {
            	case 1:
                	tetris_score += 1; break;

                case 2:
                	tetris_score += 4; break;

                case 3:
                	tetris_score += 8; break;
            }

        	tetris_clear_line(y);
            tetris_shift_stack(y);
            tetris_draw_stack();
            tetris_draw_score();
            ++y;
            ++tetris_tos;
        }
    }
}

void tetris_shift_stack(int y)
{
	int x;

    while (y > 0)
    {
    	for (x = 0; x < TETRIS_WIDTH; ++x)
        	tetris_stack[x][y] = tetris_stack[x][y - 1];
    	--y;
    }

	for (x = 0; x < TETRIS_WIDTH; ++x)
    	tetris_stack[x][0] = TETRIS_BLOCK_FREE_COLOR;
}

void tetris_get_input()
{
	if (JOYSTICK_PIN_LEFT == 0)
    	tetris_move_left();
    else if (JOYSTICK_PIN_RIGHT == 0)
    	tetris_move_right();
}

void tetris_put_brik()
{
	int x, y;

    for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
    	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        	if (tetris_brik_y + y >= 0 && tetris_tetrominos[tetris_brik_index][y] & (0x01 << x))
            	tetris_stack[tetris_brik_x + x][tetris_brik_y + y] = tetris_brik_color;
}

void tetris_draw_score()
{

    char* str_score = "      ";		// 6 digit
    point score_s = {2, 2};
    rectangle score_r = {6 * 11 + 11 , 10, 6 * 11, 16};

    itoa(tetris_score * 10, str_score);
    fill_rectangle(score_r, TETRIS_BACKGROUND_COLOR);
    draw_string(str_score, score_r.p, score_s, BLUE);
}

void tetris_draw_tos()
{
    char str_dig[] = "  ";

    point tos_p = {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH - TETRIS_BLOCK_HEIGHT / 2 + 4 * 11 + 2
    				, TETRIS_BORDER_SIDE_Y + TETRIS_BORDER_HEIGHT / 2 - TETRIS_BLOCK_HEIGHT / 2 - 4 * 8};

    rectangle tos_rect = {TETRIS_BORDER_RIGHT_X + TETRIS_BORDER_WIDTH + TETRIS_BLOCK_WIDTH - TETRIS_BLOCK_HEIGHT / 2 + 4 * 11 + 2
    				, TETRIS_BORDER_SIDE_Y + TETRIS_BORDER_HEIGHT / 2 - TETRIS_BLOCK_HEIGHT / 2 - 4 * 8
                    , 2 * 6 * 2, 2 * 8};

    point s = {2, 2};

    itoa(TETRIS_HEIGHT - tetris_tos, str_dig);
    fill_rectangle(tos_rect, TETRIS_BACKGROUND_COLOR);
    draw_string(str_dig, tos_p, s, BLUE);
}

TETRIS_BOOL tetris_check_collision()
{
	signed int y, x;

    // End of stack
	if (tetris_brik_y + TETRIS_TETROMINO_HEIGHT >= TETRIS_HEIGHT)
    	return TETRIS_TRUE;

    // Stacked blocks
	for (y = 0; y < TETRIS_TETROMINO_HEIGHT; ++y)
    	for (x = 0; x < TETRIS_TETROMINO_WIDTH; ++x)
        	if (tetris_brik_y + y + 1 >= 0 && (tetris_tetrominos[tetris_brik_index][y] & (0x01 << x)))
            	if (tetris_stack[tetris_brik_x + x][tetris_brik_y + y + 1] != TETRIS_BLOCK_FREE_COLOR)
                	return TETRIS_TRUE;

	return TETRIS_FALSE;
}

TETRIS_BOOL tetris_check_gameover()
{
	int insertion_y = tetris_brik_real_y();

	if (insertion_y < tetris_tos)
    	tetris_tos = insertion_y;

	if (tetris_tos < 0)
    	tetris_gameover = TETRIS_TRUE;

    tetris_draw_tos();

    return tetris_gameover;
}
