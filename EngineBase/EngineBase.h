#pragma once

#ifdef BASE_DLL
#define BASE_API __declspec(dllexport)
#else
#define BASE_API __declspec(dllimport)
#endif

#ifdef ENGINE_DLL_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif