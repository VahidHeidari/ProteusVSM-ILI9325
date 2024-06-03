#include "tft-ili9325.h"

void tft_ili9325_reset()
{
	TFT_ILI9325_RESET_0;
    delay_ms(50);
    delay_ms(50);
    TFT_ILI9325_RESET_1;
    delay_ms(50);
    delay_ms(50);
}

void tft_ili9325_wr_cmd(unsigned char index, unsigned int val)
{
	TFT_ILI9325_RS_0;
    TFT_ILI9325_CS_0;

    TFT_ILI9325_WR_DATA = 0x00;
    TFT_ILI9325_WR_DATA_LOW = index;
    TFT_ILI9325_WR_0;
    TFT_ILI9325_WR_1;

    TFT_ILI9325_RS_1;

    TFT_ILI9325_WR_DATA = (unsigned char)(val >> 8);
    TFT_ILI9325_WR_DATA_LOW = (unsigned char)val;
    TFT_ILI9325_WR_0;
    TFT_ILI9325_WR_1;

    TFT_ILI9325_CS_1;
}

void tft_ili9325_init()
{
	TFT_ILI9325_CONTROL_DDR = 0xFC;
    TFT_ILI9325_WR_DATA_DDR = 0xFF;
    TFT_ILI9325_WR_DATA_LOW_DDR = 0xff;

    tft_ili9325_reset();
    TFT_ILI9325_CS_1;
    TFT_ILI9325_WR_1;
    TFT_ILI9325_RD_1;

	tft_ili9325_wr_cmd(0xe3, 0x3008); // set internal timming
    tft_ili9325_wr_cmd(0xe7, 0x0012);
    tft_ili9325_wr_cmd(0xef, 0x1231);
    tft_ili9325_wr_cmd(0x01, 0x0100); // set SS and SM bit
    tft_ili9325_wr_cmd(0x02, 0x0700);
    tft_ili9325_wr_cmd(0x03, 0x1030); // set GRAM write direction and BFR = 1.
    tft_ili9325_wr_cmd(0x04, 0x0000); // Resize register
    tft_ili9325_wr_cmd(0x08, 0x0202); // set the back proch and front proch
    tft_ili9325_wr_cmd(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
    tft_ili9325_wr_cmd(0x0a, 0x0000); // FMARK function
    tft_ili9325_wr_cmd(0x0c, 0x0000); // RGB interface setting
    tft_ili9325_wr_cmd(0x0d, 0x0000); // Frame marker Position
    tft_ili9325_wr_cmd(0x0f, 0x0000); // RGB interface polarity
    /***************power on  sequence********************/
    tft_ili9325_wr_cmd(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
    tft_ili9325_wr_cmd(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
    tft_ili9325_wr_cmd(0x12, 0x0000); // VREG1OUT voltage
    tft_ili9325_wr_cmd(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
    delay_ms(50);			  // Dis-charge capacitor power voltage
    delay_ms(50);
    delay_ms(50);
    delay_ms(50);
    tft_ili9325_wr_cmd(0x10, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
    tft_ili9325_wr_cmd(0x11, 0x0227); // R11h=0x0221 at VCI=3.3v, DC0[2:0], VC[2:0]
    delay_ms(50);			  // Delay 50ms
    tft_ili9325_wr_cmd(0x12, 0x001c); // External reference voltage=Vci;
    delay_ms(50);
    tft_ili9325_wr_cmd(0x20, 0x0000); // GRAM horizontal address
    tft_ili9325_wr_cmd(0x21, 0x0000); // GRAM vertical address
    /******************Adjust the Gamma curve*****************/
    tft_ili9325_wr_cmd(0x30, 0x0007);
    tft_ili9325_wr_cmd(0x31, 0x0302);
    tft_ili9325_wr_cmd(0x32, 0x0105);
    tft_ili9325_wr_cmd(0x35, 0x0206);
    tft_ili9325_wr_cmd(0x36, 0x0808);
    tft_ili9325_wr_cmd(0x37, 0x0206);
    tft_ili9325_wr_cmd(0x38, 0x0504);
    tft_ili9325_wr_cmd(0x39, 0x0007);
    tft_ili9325_wr_cmd(0x3c, 0x0105);
    tft_ili9325_wr_cmd(0x3d, 0x0808);
    /***************** Set GRAM area ***********************/
    tft_ili9325_wr_cmd(0x50, 0x0000); // Horizontal GRAM start address
    tft_ili9325_wr_cmd(0x51, 0x00ef); // Horizontal GRAM end address
    tft_ili9325_wr_cmd(0x52, 0x0000); // Vertical GRAM start address
    tft_ili9325_wr_cmd(0x53, 0x013f); // Vertical GRAM start address
    tft_ili9325_wr_cmd(0x60, 0xA700); // Gate scan line
    tft_ili9325_wr_cmd(0x61, 0x0001); // NDL, VLE, REV
    tft_ili9325_wr_cmd(0x6a, 0x0000); // set scrolling line
    /***************** Partial display control ******************/
    tft_ili9325_wr_cmd(0x80, 0x0000);
    tft_ili9325_wr_cmd(0x81, 0x0000);
    tft_ili9325_wr_cmd(0x82, 0x0000);
    tft_ili9325_wr_cmd(0x83, 0x0000);
    tft_ili9325_wr_cmd(0x84, 0x0000);
    tft_ili9325_wr_cmd(0x85, 0x0000);
    /**************** Panel control **********************/
    tft_ili9325_wr_cmd(0x90, 0x0010);
    tft_ili9325_wr_cmd(0x92, 0x0000);
    tft_ili9325_wr_cmd(0x93, 0x0003);
    tft_ili9325_wr_cmd(0x95, 0x0110);
    tft_ili9325_wr_cmd(0x97, 0x0000);
    tft_ili9325_wr_cmd(0x98, 0x0000);
    tft_ili9325_wr_cmd(0x07, 0x0133); // 262k color and display ON
}

void tft_ili9325_wr_reg(unsigned char index)
{
	TFT_ILI9325_RS_0;
    TFT_ILI9325_CS_0;

    TFT_ILI9325_WR_DATA = 0x00;
    TFT_ILI9325_WR_DATA_LOW = index;
    TFT_ILI9325_WR_0;
    TFT_ILI9325_WR_1;

    TFT_ILI9325_CS_1;
    TFT_ILI9325_RS_1;
}

void tft_ili9325_wr_data(unsigned int val)
{
    TFT_ILI9325_CS_0;

    TFT_ILI9325_WR_DATA = (unsigned char)(val >> 8);
    TFT_ILI9325_WR_DATA_LOW = (unsigned char)val;
    TFT_ILI9325_WR_0;
    TFT_ILI9325_WR_1;

    TFT_ILI9325_CS_1;
}

unsigned int tft_ili9325_read_data()
{
	unsigned int data = 0;

    TFT_ILI9325_WR_DATA = 0xFF;
    TFT_ILI9325_WR_DATA_LOW = 0xff;
    TFT_ILI9325_WR_DATA_DDR = 0x00;
    TFT_ILI9325_WR_DATA_LOW_DDR = 0x00;

    TFT_ILI9325_CS_0;
    TFT_ILI9325_RS_1;
    TFT_ILI9325_WR_1;

    TFT_ILI9325_RD_0;
	delay_us(50);
	data = TFT_ILI9325_WR_DATA_PIN;
    data <<= 8;
    data |= TFT_ILI9325_WR_DATA_LOW_PIN;
    TFT_ILI9325_RD_1;

    TFT_ILI9325_CS_1;

    TFT_ILI9325_WR_DATA_DDR = 0xFF;
    TFT_ILI9325_WR_DATA_LOW_DDR = 0xff;
    TFT_ILI9325_WR_DATA = 0x00;
    TFT_ILI9325_WR_DATA_LOW = 0x00;

	return data;
}
