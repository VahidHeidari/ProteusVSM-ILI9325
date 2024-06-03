#include "ili9325.h"
#include "logger.h"
#include "vsm.hpp"

extern "C" {

__declspec(dllexport) IACTIVEMODEL* createactivemodel(CHAR* device, ILICENCESERVER* ils)
{
#ifdef DEBUG_LOG
	ofs << "Hi from active model :)  -> `" << device << "'" << std::endl;
#endif

	// Exported constructor for active component models.
	if (ils->authorize(ILI9325::AUTHORIZE_KEY)) {
#ifdef DEBUG_LOG
		ofs << "  Successfull! :D" << std::endl;
#endif
		ILI9325* dev = new ILI9325();
		return dev;
	}

#ifdef DEBUG_LOG
	ofs << "  Failed! :(" << std::endl;
#endif
	return nullptr;
}

__declspec(dllexport) VOID deleteactivemodel(IACTIVEMODEL* device)
{
#ifdef DEBUG_LOG
	ofs << "Released :)" << std::endl;
#endif

	// Exported destructor for active component models.
	delete static_cast<ILI9325*>(device);
}

__declspec(dllexport) IDSIMMODEL* createdsimmodel(CHAR* device, ILICENCESERVER* ils)
{
#ifdef DEBUG_LOG
	ofs << "Hi from dsim model :)  -> `" << device << "'" << std::endl;
#endif

	// Exported constructor for active component models.
	if (ils->authorize(ILI9325::AUTHORIZE_KEY)) {
#ifdef DEBUG_LOG
		ofs << "  Successfull! :D" << std::endl;
#endif
		ILI9325* dev = new ILI9325();
		return dev;
	}

#ifdef DEBUG_LOG
	ofs << "  Failed! :(" << std::endl;
#endif
	return nullptr;
}

__declspec(dllexport) VOID deletedsimmodel(IDSIMMODEL* model)
{
#ifdef DEBUG_LOG
	ofs << "Released dsim model :)" << std::endl;
#endif

	// Exported destructor for active component models.
	delete static_cast<ILI9325*>(model);
}

}		// extern "C"
