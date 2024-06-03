#include "config.h"
#include "graphics.h"
#include "tft-ili9325.h"
#include "tetris.h"
#include "rtc.h"

void main()
{
	joystick_init();
	tft_ili9325_init();
    clear_screen(RGB(0x8, 0x12, 0x8));
    tetris_run();

	while (1)
		continue;
}
