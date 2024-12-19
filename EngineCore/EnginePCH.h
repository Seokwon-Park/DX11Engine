#pragma once

#include <EnginePlatform/EnginePCH.h>

#include "Graphics/EngineDeviceContext.h"
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
