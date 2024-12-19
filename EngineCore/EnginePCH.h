#pragma once

#include <EnginePlatform/EnginePCH.h>

#include "Graphics/EngineDeviceContext.h"
#include <d3d11.h>
#include <d3dcompiler.h> 
#include <wrl.h>

// 라이브러리들
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
// GetHighPerFormanceAdapter 등등을 위해서는 모니터 정보나 그래픽카드 정보를 얻어와야하는데
// 이녀석이 그 함수들을 가지고 있다.
#pragma comment(lib, "DXGI") 

using namespace Microsoft::WRL;
