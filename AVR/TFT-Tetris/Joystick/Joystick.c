#include "joystick.h"

void joystick_init()
{
	JOYSTICK_PORT = 0xFF;
    JOYSTICK_DDR = 0xF0;
}
