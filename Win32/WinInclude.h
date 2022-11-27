#pragma once

/*
*  including the windows header
*  without the overhead
*  yay
*/

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define NOCOMM

#include <Windows.h>

/* 
*  now the preprocessor shit
*  debug strings abstracted in
*  release builds
*/

#ifdef _DEBUG

#define output_debug(stra) OutputDebugStringA(stra)\

#else

#define output_debug(stra) \

#endif