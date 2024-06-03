#include "ili9325.h"

#include <string.h>

#include <algorithm>
#include <iomanip>

#include "logger.h"

ILI9325::ILI9325() :
	comp(nullptr),
	inst(nullptr),
	ckt(nullptr),
	reg(0),
	data(0),
	regx(0),
	regy(0),
	pixels(new int[NUM_PIXELS])
{
	memset(ctrl_pins, 0, sizeof(ctrl_pins[0]) * Pins::PIN_CNT);
	memset(db_pins, 0, sizeof(db_pins[0]) * NUM_DB_PINS);
	memset(pixels, 0xff, sizeof(pixels[0]) * NUM_PIXELS);

	/*SetPixel(10, 10, 0xff0000);
	SetPixel(20, 10, 0x00ff00);
	SetPixel(30, 10, 0x0000ff);
	SetPixel(10, 20, RED);
	SetPixel(0, 10, YELLOW);
	SetPixel(239, 10, CYAN);
	SetPixel(0, 0, MAGENTA);
	SetPixel(0, 319, DARKGREEN);*/
}

ILI9325::~ILI9325()
{
	delete[] pixels;
}

VOID ILI9325::initialize(ICOMPONENT* cpt)
{
	// Store ICOMPONENT interface and initialize.
	comp = cpt;
	comp->getsymbolarea(1, &lcd_box);

#ifdef DEBUG_LOG
	ofs << "initialize(" << static_cast<void*>(cpt) << ")" << std::endl;

	BOX lcd_box;
	bool res = comp->getsymbolarea(-1, &lcd_box);
	ofs << "   res:" << std::boolalpha << res
		<< "  box: x1:" << lcd_box.x1
		<< " y1:" << lcd_box.y1
		<< " x2:" << lcd_box.x2
		<< " y2:" << lcd_box.y2 << std::endl;

	res = comp->getsymbolarea(0, &lcd_box);
	ofs << "   res:" << std::boolalpha << res
		<< "  box: x1:" << lcd_box.x1
		<< " y1:" << lcd_box.y1
		<< " x2:" << lcd_box.x2
		<< " y2:" << lcd_box.y2 << std::endl;

	res = comp->getsymbolarea(1, &lcd_box);
	ofs << "   res:" << std::boolalpha << res
		<< "  box: x1:" << lcd_box.x1
		<< " y1:" << lcd_box.y1
		<< " x2:" << lcd_box.x2
		<< " y2:" << lcd_box.y2 << std::endl;

	res = comp->getsymbolarea(2, &lcd_box);
	ofs << "   res:" << std::boolalpha << res
		<< "  box: x1:" << lcd_box.x1
		<< " y1:" << lcd_box.y1
		<< " x2:" << lcd_box.x2
		<< " y2:" << lcd_box.y2 << std::endl;

	POINT point;
	bool resp = comp->getmarker("TFTLCDPANEL", &point);
	ofs << "  resp:" << std::boolalpha << resp
		<< "  point: x:" << point.x
		<< " y:" << point.y << std::endl;
#endif
}

ISPICEMODEL* ILI9325::getspicemodel(CHAR* primitive)
{
#ifdef DEBUG_LOG
	ofs << "GetSpiceModel(" << primitive << ")" << std::endl;
#endif

	return nullptr;
}

IDSIMMODEL* ILI9325::getdsimmodel(CHAR* primitive)
{
#ifdef DEBUG_LOG
	ofs << "GetDsimModel(" << primitive << ")" << std::endl;
#endif

	return this;
}

VOID ILI9325::plot(ACTIVESTATE state)
{
#ifdef DEBUG_LOG
	ofs << "plot(" << state << ")" << std::endl;
#endif

	//comp->drawstate(state);
	comp->drawsymbol(-1);
	comp->drawsymbol(0);
	Draw();
}

static const char* GetActiveDataTypesName(ACTIVEDATATYPES t)
{
	switch (t) {
	case ACTIVEDATATYPES::ADT_VOID:			return "ADT_VOID";
	case ACTIVEDATATYPES::ADT_REAL:			return "ADT_REAL";
	case ACTIVEDATATYPES::ADT_BOOLEAN:		return "ADT_BOOLEAN";
	case ACTIVEDATATYPES::ADT_INTEGER:		return "ADT_INTEGER";
	case ACTIVEDATATYPES::ADT_STATE:		return "ADT_STATE";
	case ACTIVEDATATYPES::ADT_PINVOLTAGE:	return "ADT_PINVOLTAGE";
	case ACTIVEDATATYPES::ADT_PINSTATE:		return "ADT_PINSTATE";
	case ACTIVEDATATYPES::ADT_WIREINFO:		return "ADT_WIREINFO";
	case ACTIVEDATATYPES::ADT_SPICEDATA:	return "ADT_SPICEDATA";
	case ACTIVEDATATYPES::ADT_DSIMDATA:		return "ADT_DSIMDATA";
	case ACTIVEDATATYPES::ADT_USER:			return "ADT_USER";
	default: break;
	}
	return "???";
}

VOID ILI9325::animate(INT element, ACTIVEDATA *newstate)
{
#ifdef DEBUG_LOG
	ofs << "animate(" << element << ", " << static_cast<void*>(newstate) << ")" << std::endl;
	ofs << "  type:" << newstate->type << "   " << GetActiveDataTypesName(newstate->type) << std::endl;
#endif

	Draw();
}

BOOL ILI9325::actuate (WORD key, INT x, INT y, DWORD flags)
{
#ifdef DEBUG_LOG
	ofs << "actuate(" << key << ", " << x << ", " << y << ", "
		<< std::hex << flags << std::dec << ")" << std::endl;
#endif

	return FALSE;
}


INT ILI9325::isdigital(CHAR* pinname)
{
#ifdef DEBUG_LOG
ofs << "isdigital(" << pinname << ")" << std::endl;
#endif

return 1;
}

VOID ILI9325::setup(IINSTANCE* instance, IDSIMCKT* dsim)
{
	inst = instance;
	ckt = dsim;

	// Power pins
	ctrl_pins[Pins::PIN_GND] = inst->getdsimpin("GND", true);
	ctrl_pins[Pins::PIN_VCC] = inst->getdsimpin("VCC", true);

	// Control pins
	ctrl_pins[Pins::PIN_REST] = inst->getdsimpin("REST", true);
	ctrl_pins[Pins::PIN_CS]   = inst->getdsimpin("CS", true);
	ctrl_pins[Pins::PIN_RS]   = inst->getdsimpin("RS", true);
	ctrl_pins[Pins::PIN_WR]   = inst->getdsimpin("WR", true);
	ctrl_pins[Pins::PIN_RD]   = inst->getdsimpin("RD", true);
	ctrl_pins[Pins::PIN_IMO]  = inst->getdsimpin("IMO", true);
	for (int i = 0; i < Pins::PIN_CNT; ++i)
		ctrl_pins[i]->setstate(STATE::FLT);

	// Data bus pins
	db_pins[ 0] = inst->getdsimpin("DB1", true);
	db_pins[ 1] = inst->getdsimpin("DB2", true);
	db_pins[ 2] = inst->getdsimpin("DB3", true);
	db_pins[ 3] = inst->getdsimpin("DB4", true);
	db_pins[ 4] = inst->getdsimpin("DB5", true);
	db_pins[ 5] = inst->getdsimpin("DB6", true);
	db_pins[ 6] = inst->getdsimpin("DB7", true);
	db_pins[ 7] = inst->getdsimpin("DB8", true);
	db_pins[ 8] = inst->getdsimpin("DB10", true);
	db_pins[ 9] = inst->getdsimpin("DB11", true);
	db_pins[10] = inst->getdsimpin("DB12", true);
	db_pins[11] = inst->getdsimpin("DB13", true);
	db_pins[12] = inst->getdsimpin("DB14", true);
	db_pins[13] = inst->getdsimpin("DB15", true);
	db_pins[14] = inst->getdsimpin("DB16", true);
	db_pins[15] = inst->getdsimpin("DB17", true);
	for (int i = 0; i < NUM_DB_PINS; ++i)
		ctrl_pins[i]->setstate(STATE::FLT);
	databus = instance->getbuspin("LCD_DBUS", db_pins, NUM_DB_PINS);
	databus->settiming(100, 100, 100);
	databus->setstates(SHI, SLO, FLT);

#ifdef DEBUG_LOG
	ofs << "Setup(inst:" << static_cast<void*>(instance)
		<< ", dsim:" << static_cast<void*>(dsim) << ")" << std::endl;
#endif
}

static const char* GetRunModesName(RUNMODES rm)
{
	switch (rm) {
	case RUNMODES::RM_BATCH:	return "RM_BATCH";
	case RUNMODES::RM_START:	return "RM_START";
	case RUNMODES::RM_STOP:		return "RM_STOP";
	case RUNMODES::RM_SUSPEND:	return "RM_SUSPEND";
	case RUNMODES::RM_ANIMATE:	return "RM_ANIMATE";
	case RUNMODES::RM_STEPTIME:	return "RM_STEPTIME";
	case RUNMODES::RM_STEPOVER:	return "RM_STEPOVER";
	case RUNMODES::RM_STEPINTO:	return "RM_STEPINTO";
	case RUNMODES::RM_STEPOUT:	return "RM_STEPOUT";
	case RUNMODES::RM_STEPTO:	return "RM_STEPTO";
	case RUNMODES::RM_META:		return "RM_META";
	case RUNMODES::RM_DUMP:		return "RM_DUMP";
	default: break;
	}
	return "???";
}

VOID ILI9325::runctrl(RUNMODES mode)
{
#ifdef DEBUG_LOG
	ofs << "runctrl(mode:" << GetRunModesName(mode) << ")" << std::endl;
#endif
}

VOID ILI9325::actuate(REALTIME time, ACTIVESTATE newstate)
{
#ifdef DEBUG_LOG
	ofs << "actuate(time:" << time << ", newstate:" << newstate << ")" << std::endl;
#endif
}

BOOL ILI9325::indicate(REALTIME time, ACTIVEDATA* newstate)
{
#ifdef DEBUG_LOG
	ofs << "indicate(time:" << time << ", newstate:" << static_cast<void*>(newstate) << ")" << std::endl;
#endif

	return FALSE;
}

VOID ILI9325::simulate(ABSTIME time, DSIMMODES mode)
{
	const Funcs func = GetFunc(ctrl_pins);
	switch (func) {
	case Funcs::F_SET_IDX:
		reg = databus->getbusvalue();
		break;

	case Funcs::F_WR_GRAM:
		data = databus->getbusvalue();
		if (reg == 0x20)
			regx = data;
		else if (reg == 0x21)
			regy = data;
		else if (reg == 0x22) {
			//const int r = ((data >> 11) & 0x001f);// << 3;
			//const int g = ((data >> 5) & 0x3f);// << 2;
			//const int b = (data & 0x001f);// << 3;
			const int r = (data & 0xf800) >> 8;
			const int g = (data & 0x07e0) >> 3;
			const int b = (data & 0x001f) << 3;
			const int c = MAKECOLOUR(r, g, b);
			SetPixel(regx++, regy, c);
			if (regx >= WIDTH) {
				regx = 0;
				if (++regy >= HEIGHT)
					regy = 0;
			}
		}
		break;

	default: break;
	}

#ifdef DEBUG_LOG
#define CTRLPIN(P) (ishigh(ctrl_pins[P]->istate()) ? '1' : islow(ctrl_pins[P]->istate()) ? '0' : '?')
	static ABSTIME old_tm = 0;

	const char* func_name = GetFuncName(ctrl_pins);
	if (strcmp(func_name, "???") == 0)
		return;

	ofs << "simulate(time:" << time
		<< ", mode:" << std::hex << mode << std::dec << ")"
		//<< " dt:" << (time - old_tm)
		<< "   ctrl:" << CTRLPIN(Pins::PIN_GND) << CTRLPIN(Pins::PIN_VCC)
		<< " " << CTRLPIN(Pins::PIN_REST)
		<< CTRLPIN(Pins::PIN_CS) << CTRLPIN(Pins::PIN_RS)
		<< CTRLPIN(Pins::PIN_WR) << CTRLPIN(Pins::PIN_RD)
		<< ' ' << CTRLPIN(Pins::PIN_IMO)
		<< "   DB:" << std::hex << std::setw(4) << std::setfill('0') << databus->getbusvalue() << std::dec
		<< "   func:" << func_name
		<< "   x:" << regx << " y:" << regy
		<< "   reg:" << std::hex << reg << std::dec
		<< std::endl;

	old_tm = time;
#undef CTRLPIN
#endif
}

VOID ILI9325::callback(ABSTIME time, EVENTID eventid)
{
#ifdef DEBUG_LOG
	ofs << "callback(time:" << time << ", eventid:" << eventid << ")" << std::endl;
#endif
}


ILI9325::Funcs ILI9325::GetFunc(IDSIMPIN** pins)
{
	if (islow(pins[ILI9325::Pins::PIN_RS]->istate())) {
		if (ishigh(pins[ILI9325::Pins::PIN_WR]->istate()) && islow(pins[ILI9325::Pins::PIN_RD]->istate()))
			return Funcs::F_RD_STAT;

		if (islow(pins[ILI9325::Pins::PIN_WR]->istate()) && ishigh(pins[ILI9325::Pins::PIN_RD]->istate()))
			return Funcs::F_SET_IDX;

		return Funcs::F_INVALID;
	}

	if (ishigh(pins[ILI9325::Pins::PIN_RS]->istate())) {
		if (ishigh(pins[ILI9325::Pins::PIN_WR]->istate()) && islow(pins[ILI9325::Pins::PIN_RD]->istate()))
			return Funcs::F_RD_GRAM;

		if (islow(pins[ILI9325::Pins::PIN_WR]->istate()) && ishigh(pins[ILI9325::Pins::PIN_RD]->istate()))
			return Funcs::F_WR_GRAM;

		return Funcs::F_INVALID;
	}

	return Funcs::F_INVALID;
}

const char* ILI9325::GetFuncName(IDSIMPIN** pins)
{
	const Funcs fnc = GetFunc(pins);
	switch (fnc) {
	case Funcs::F_SET_IDX:	return "SET_INDEX";
	case Funcs::F_RD_STAT:	return "READ_STATUS";
	case Funcs::F_RD_GRAM:	return "READ_GRAM";
	case Funcs::F_WR_GRAM:	return "WRITE_GRAM";
	default: break;
	}
	return "???";
}


int ILI9325::GetPixel(int x, int y) const
{
	return pixels[y * WIDTH + x];
}

void ILI9325::SetPixel(int x, int y, int c)
{
	const int idx = (HEIGHT - 1 - y) * WIDTH + x;
	if (idx < 0 || idx >= WIDTH * HEIGHT)
		return;

	pixels[idx] = c;
}

void ILI9325::Draw() const
{
#ifdef FRAME_SKIP
	static int frame = 0;
	if (++frame < NUM_FRAME_SKIPS)
		return;
	frame = 0;
#endif

	//comp->drawsymbol(-1);

	const double lcd_w = std::abs(lcd_box.x2 - lcd_box.x1) - SCR_X_OFF_2;
	const double lcd_h = std::abs(lcd_box.y2 - lcd_box.y1) - SCR_Y_OFF_2;
	const double pixel_w = lcd_w / WIDTH;
	const double pixel_h = lcd_h / HEIGHT;
	double py = lcd_box.y1 + SCR_Y_OFF;

	comp->begincache(*const_cast<BOX*>(&lcd_box));
	comp->drawsymbol(1);
	comp->setpenwidth(0);
	for (int j = 0; j < HEIGHT; ++j, py += pixel_h) {
		double px = lcd_box.x1 + SCR_X_OFF;
		int idx = j * WIDTH;
		for (int i = 0; i < WIDTH; ++i, px += pixel_w, ++idx) {
			const int c = pixels[idx];
			comp->setbrushcolour(c);
			comp->setpencolour(c);

			BOX bx = {
				static_cast<int>(px),
				static_cast<int>(py),
				static_cast<int>(px + pixel_w),
				static_cast<int>(py - pixel_h)
			};
			comp->drawbox(bx);
		}
	}
	comp->endcache();

#ifdef DEBUG_LOG
	ofs << "  BOX(" << lcd_box.x1
		<< ", " << lcd_box.y1
		<< ", " << lcd_box.x2
		<< ", " << lcd_box.y2 << ")" << std::endl;
	ofs << "  lcd_w:" << lcd_w << ", lcd_h:" << lcd_h << std::endl;
	ofs << " pixel_w:" << pixel_w << ", pixel_h:" << pixel_h << std::endl;
#endif
}
