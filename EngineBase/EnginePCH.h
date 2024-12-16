#pragma once

#define ENGINE_DLL_BUILD

#ifdef _WIN64 
	#include <Windows.h>
#endif

#include <cmath>
#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

#include "Object.h"
#include "EngineBase.h"
#include "EngineDebug.h"
#include "EngineLogger.h"



