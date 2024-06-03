#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "config.h"

#define JOYSTICK_PORT			PORTC
#define JOYSTICK_DDR			DDRC
#define JOYSTICK_PIN			PINC

#define JOYSTICK_PORT_LEFT		JOYSTICK_PORT.0
#define JOYSTICK_DDR_LEFT		JOYSTICK_DDR.0
#define JOYSTICK_PIN_LEFT		JOYSTICK_PIN.0

#define JOYSTICK_PORT_RIGHT		JOYSTICK_PORT.1
#define JOYSTICK_DDR_RIGHT		JOYSTICK_DDR.1
#define JOYSTICK_PIN_RIGHT		JOYSTICK_PIN.1

#pragma used+

void joystick_init();

#pragma used-

#endif
