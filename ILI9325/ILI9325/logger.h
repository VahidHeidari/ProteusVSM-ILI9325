#pragma once

// Uncomment below line for debugging logs.
//#define DEBUG_LOG

#ifdef DEBUG_LOG
#include <fstream>

extern std::ofstream ofs;
#endif

// Uncomment below line to skip frames for faster animations.
//#define FRAME_SKIP
#ifdef FRAME_SKIP
constexpr int NUM_FRAME_SKIPS = 5;
#endif
