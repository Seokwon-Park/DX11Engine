#pragma once

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineMath.h>

enum class ERendererAPI
{
	DirectX11,
	None
};
// Ό³Έν :
class UEngineDeviceContext
{
public:
	// constrcuter destructer
	ENGINE_API UEngineDeviceContext();
	ENGINE_API virtual ~UEngineDeviceContext();

	ENGINE_API virtual void Init(const UEngineWindow& _Window);
	ENGINE_API virtual void ClearRenderTarget();
	ENGINE_API virtual void SwapBuffers();
	ENGINE_API inline void SetClearColor(FColor _Color) { ClearColor = _Color; }

	ENGINE_API inline void SetRendererAPI(ERendererAPI _API) { API = _API; }
	ENGINE_API inline ERendererAPI GetRendererAPI() { return API;  }
protected:
	ERendererAPI API;
	FColor ClearColor;

private:

};

