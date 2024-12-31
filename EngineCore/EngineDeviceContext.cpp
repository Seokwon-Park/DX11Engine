#include "EnginePCH.h"
#include "EngineDeviceContext.h"
#include "EngineCore.h"
#include <EngineCore/DirectX11/DX11DeviceContext.h>

UEngineDeviceContext::UEngineDeviceContext()
{
}

UEngineDeviceContext::~UEngineDeviceContext()
{
}

void UEngineDeviceContext::Init(const UEngineWindow& _Window) {}
void UEngineDeviceContext::ClearRenderTarget() {}
void UEngineDeviceContext::SwapBuffers() {}

UEngineDeviceContext* UEngineDeviceContext::Create()
{
	ERendererAPI API = UEngineCore::GetRendererAPI();
	if (API == ERendererAPI::None)
	{
		MSGASSERT("렌더링 API가 설정되지 않았습니다.");
	}
	switch (API)
	{
	case ERendererAPI::DirectX11:
		return new DX11DeviceContext();
		break;
	case ERendererAPI::None:
		break;
	default:
		break;
	}
	return nullptr;
}
