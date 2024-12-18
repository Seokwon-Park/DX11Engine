#pragma once

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineMath.h>


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
protected:
	FColor ClearColor;

private:

};

