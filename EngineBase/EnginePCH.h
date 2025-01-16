#pragma once

#define BASE_DLL

#ifdef _WIN64 
	#include <Windows.h>
	#define NOMINMAX
#endif

#include <map>
#include <cmath>
#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

#include "Object.h"
#include "EngineBase.h"
#include "EngineDebug.h"
#include "EngineLogger.h"



