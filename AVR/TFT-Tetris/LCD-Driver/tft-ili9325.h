#ifndef TFT_ILI9325_H
#define TFT_ILI9325_H

#include <delay.h>

#include "config.h"

#define TFT_ILI9325_CONTROL_PORT	PORTD
#define TFT_ILI9325_CONTROL_DDR		DDRD
#define TFT_ILI9325_CONTROL_PIN		PIND

#define TFT_ILI9325_WR_DATA			PORTB
#define TFT_ILI9325_WR_DATA_DDR		DDRB
#define TFT_ILI9325_WR_DATA_PIN		PINB

#define TFT_ILI9325_WR_DATA_LOW		PORTA
#define TFT_ILI9325_WR_DATA_LOW_DDR	DDRA
#define TFT_ILI9325_WR_DATA_LOW_PIN	PINA

#define TFT_ILI9325_RESET			TFT_ILI9325_CONTROL_PORT.2
#define TFT_ILI9325_CS				TFT_ILI9325_CONTROL_PORT.3
#define TFT_ILI9325_RS				TFT_ILI9325_CONTROL_PORT.4
#define TFT_ILI9325_WR				TFT_ILI9325_CONTROL_PORT.5
#define TFT_ILI9325_RD				TFT_ILI9325_CONTROL_PORT.6

#define TFT_ILI9325_RESET_1			TFT_ILI9325_RESET = 1
#define TFT_ILI9325_RESET_0			TFT_ILI9325_RESET = 0
#define TFT_ILI9325_CS_1			TFT_ILI9325_CS = 1
#define TFT_ILI9325_CS_0			TFT_ILI9325_CS = 0
#define TFT_ILI9325_RS_1			TFT_ILI9325_RS = 1
#define TFT_ILI9325_RS_0			TFT_ILI9325_RS = 0
#define TFT_ILI9325_WR_1			TFT_ILI9325_WR = 1
#define TFT_ILI9325_WR_0			TFT_ILI9325_WR = 0
#define TFT_ILI9325_RD_1			TFT_ILI9325_RD = 1
#define TFT_ILI9325_RD_0			TFT_ILI9325_RD = 0

#pragma used+

void tft_ili9325_init();
void tft_ili9325_reset();
void tft_ili9325_wr_cmd(unsigned char index, unsigned int val);
void tft_ili9325_wr_reg(unsigned char index);
void tft_ili9325_wr_data(unsigned int val);
unsigned int tft_ili9325_read_data();

#pragma used-

#endif
