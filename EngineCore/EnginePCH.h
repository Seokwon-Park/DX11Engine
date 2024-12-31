#pragma once

#define ENGINE_DLL_BUILD

#ifdef _WIN64 
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

#include "EngineDeviceContext.h"
#include <d3d11.h>
#include <d3dcompiler.h> 
#include <wrl.h>

// ���̺귯����
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
// GetHighPerFormanceAdapter ����� ���ؼ��� ����� ������ �׷���ī�� ������ ���;��ϴµ�
// �̳༮�� �� �Լ����� ������ �ִ�.
#pragma comment(lib, "DXGI") 

using namespace Microsoft::WRL;
