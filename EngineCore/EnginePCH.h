#pragma once

#define ENGINE_DLL_BUILD

#ifdef _WIN64 
#define NOMINMAX
#include <Windows.h>
#endif

#include <map>
#include <cmath>
#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineLogger.h>
#include <EnginePlatform/KeyCode.h>

#include <d3d11.h>
#include <d3dcompiler.h> 
#include <wrl.h>

#pragma comment(linker, "/NODEFAULTLIB:LIBCMTD")
// 라이브러리들
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "DXGI") 
#ifdef _DEBUG
#else
#pragma comment(lib, "box2d")
#endif


using namespace Microsoft::WRL;
