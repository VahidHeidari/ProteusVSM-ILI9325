#pragma once

#ifndef NULL
#define NULL nullptr
#endif

#include "vsm.hpp"

class ILI9325 : public IACTIVEMODEL, public IDSIMMODEL
{
public:
	// Product ID value obtained from Labcenter :P
	static constexpr DWORD AUTHORIZE_KEY = 0x12349876;

	static constexpr int WIDTH = 240;
	static constexpr int HEIGHT = 320;
	static constexpr int NUM_PIXELS = WIDTH * HEIGHT;

	static constexpr int SCR_X_OFF = 20;
	static constexpr int SCR_X_OFF_2 = SCR_X_OFF * 2;

	static constexpr int SCR_Y_OFF = 30;
	static constexpr int SCR_Y_OFF_2 = SCR_Y_OFF * 2;

	static constexpr int NUM_DB_PINS = 16;

	enum Pins {
		// Power pins
		PIN_GND,
		PIN_VCC,

		// Control pins
		PIN_REST,
		PIN_CS,
		PIN_RS,
		PIN_WR,
		PIN_RD,
		PIN_IMO,

		PIN_CNT
	};

	enum Funcs {
		// Index/Status register
		F_SET_IDX,
		F_RD_STAT,

		// GRAM
		F_WR_GRAM,
		F_RD_GRAM,

		F_INVALID
	};

	ILI9325();
	virtual ~ILI9325();

	virtual VOID initialize(ICOMPONENT* cpt);
	virtual ISPICEMODEL* getspicemodel(CHAR* primitive);
	virtual IDSIMMODEL* getdsimmodel(CHAR* primitive);
	virtual VOID plot(ACTIVESTATE state);
	virtual VOID animate(INT element, ACTIVEDATA *newstate);
	virtual BOOL actuate(WORD key, INT x, INT y, DWORD flags);

	virtual INT  isdigital(CHAR* pinname);
	virtual VOID setup(IINSTANCE* instance, IDSIMCKT* dsim);
	virtual VOID runctrl(RUNMODES mode);
	virtual VOID actuate(REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate(REALTIME time, ACTIVEDATA* newstate);
	virtual VOID simulate(ABSTIME time, DSIMMODES mode);
	virtual VOID callback(ABSTIME time, EVENTID eventid);

private:
	static Funcs GetFunc(IDSIMPIN** pins);
	static const char* GetFuncName(IDSIMPIN** pins);

	int GetPixel(int x, int y) const;
	void SetPixel(int x, int y, int c);
	void Draw() const;

	ICOMPONENT* comp;
	IINSTANCE* inst;
	IDSIMCKT* ckt;
	IDSIMPIN* ctrl_pins[Pins::PIN_CNT];
	IDSIMPIN* db_pins[NUM_DB_PINS];
	IBUSPIN* databus;

	int reg;
	int data;
	int regx;
	int regy;

	int* pixels;
	BOX lcd_box;
};
