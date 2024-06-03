#ifndef TETRIS_H
#define TETRIS_H

#include "config.h"
#include "graphics.h"
#include "joystick.h"

//#define TETRIS_BACKGROUND_COLOR		RGB(0x8, 0x12, 0x8)
#define TETRIS_BACKGROUND_COLOR		RGB(0x0, 0x12, 0x0)

typedef char TETRIS_BOOL;
#define TETRIS_TRUE					1
#define TETRIS_FALSE				0

#define TETRIS_WIDTH				10
#define TETRIS_HEIGHT				20

#define TETRIS_STACK_TOP_MARGIN		30
#define TETRIS_STACK_LEFT_MARGIN	-40
#define TETRIS_STACK_X				((SCREEN_WIDTH - ((TETRIS_WIDTH * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE)))) / 2 + TETRIS_STACK_LEFT_MARGIN)
#define TETRIS_STACK_Y				((SCREEN_HEIGHT - (TETRIS_HEIGHT * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE))) / 2 + TETRIS_STACK_TOP_MARGIN)
#define TETRIS_STACK_WIDTH			(TETRIS_WIDTH * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE))
#define TETRIS_STACK_HEIGHT			(TETRIS_HEIGHT * (TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE))

#define TETRIS_BLOCK_WIDTH	10
#define TETRIS_BLOCK_HEIGHT	10
#define TETRIS_BLOCK_SPACE	1
#define TETRIS_BLOCK_BORDER_COLOR	WHITE
#define TETRIS_BLOCK_FREE_COLOR		BLACK

#define TETRIS_BORDER_HEIGHT		((TETRIS_BLOCK_HEIGHT + TETRIS_BLOCK_SPACE) * (TETRIS_HEIGHT + 1) - TETRIS_BLOCK_SPACE)
#define TETRIS_BORDER_WIDTH			TETRIS_BLOCK_WIDTH
#define TETRIS_BORDER_SIDE_Y		TETRIS_STACK_Y
#define TETRIS_BORDER_LEFT_X		(TETRIS_STACK_X - TETRIS_BLOCK_WIDTH - TETRIS_BLOCK_SPACE)
#define TETRIS_BORDER_RIGHT_X		(TETRIS_STACK_X + (TETRIS_WIDTH * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE)))
#define TETRIS_BORDER_BOTTOM_X		TETRIS_STACK_X
#define TETRIS_BORDER_BOTTOM_Y		(TETRIS_STACK_Y + TETRIS_STACK_HEIGHT)
#define TETRIS_BORDER_BOTTOM_WIDTH	(TETRIS_WIDTH * (TETRIS_BLOCK_WIDTH + TETRIS_BLOCK_SPACE))
#define TETRIS_BORDER_BOTTOM_HEIGHT TETRIS_BLOCK_HEIGHT
#define TETRIS_BORDER_COLOR			BLACK

#define TETRIS_TETROMINO_WIDTH			3
#define TETRIS_TETROMINO_HEIGHT			3
#define TETRIS_TETROMINO_NUM_FIELDS		2
#define TETRIS_TETROMINO_WIDTH_INDEX	3
#define TETRIS_TETROMINO_HEIGHT_INDEX	4
#define TETRIS_NEXT_ROTATION_INDEX		5
#define TETRIS_NUM_TETROMINOS			15
#define tetris_brik_height()			tetris_tetrominos[tetris_brik_index][TETRIS_TETROMINO_HEIGHT_INDEX]
#define tetris_brik_width()				tetris_tetrominos[tetris_brik_index][TETRIS_TETROMINO_WIDTH_INDEX]
#define tetris_brik_real_y()			(tetris_brik_y + TETRIS_TETROMINO_HEIGHT - tetris_brik_height())
#pragma used+

void tetris_init();
void tetris_draw_border();
void tetris_draw_stack();
void tetris_run();
void tetris_move_down();
void tetris_move_right();
void tetris_move_left();
void tetris_clear_line(int y);
void tetris_draw_brik();
void tetris_clear_brik();
void tetris_check_lines();
void tetris_next_brik();
void tetris_shift_stack(int y);
void tetris_game_play();
void tetris_get_input();
void tetris_put_brik();
void tetris_draw_score();
void tetris_draw_tos();

TETRIS_BOOL tetris_check_collision();
TETRIS_BOOL tetris_check_gameover();

#pragma used-

#endif
