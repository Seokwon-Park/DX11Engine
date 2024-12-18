#pragma once

#define ENGINE_DLL_BUILD

#ifdef ENGINE_DLL_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif