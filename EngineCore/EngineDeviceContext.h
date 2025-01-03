#pragma once
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineMath.h>

// 설명 :
class UEngineDeviceContext
{
public:
	// constrcuter destructer
	ENGINE_API UEngineDeviceContext();
	ENGINE_API virtual ~UEngineDeviceContext();

	// delete Function
	UEngineDeviceContext(const UEngineDeviceContext& _Other) = delete;
	UEngineDeviceContext(UEngineDeviceContext&& _Other) noexcept = delete;
	UEngineDeviceContext& operator=(const UEngineDeviceContext& _Other) = delete;
	UEngineDeviceContext& operator=(UEngineDeviceContext&& _Other) noexcept = delete;

	ENGINE_API void Init(const UEngineWindow& _Window);
	ENGINE_API void SwapBuffers();
	ENGINE_API void ClearRenderTarget();
	ENGINE_API void CreateBackBuffer(const UEngineWindow& _Window);
	ENGINE_API void CreateRasterizer();
	ENGINE_API void CreateSwapChain(const UEngineWindow& _Window);

	ENGINE_API void DrawCall();

	ENGINE_API inline void SetClearColor(FColor _Color) { ClearColor = _Color; }
	inline ID3D11Device* GetDevice() const { return Device.Get(); }
	inline ID3D11DeviceContext* GetContext() const { return Context.Get(); }

	IDXGIAdapter* GetHighPerFormanceAdapter();

protected:
	ComPtr<IDXGIAdapter> Adapter;
	// Device - 리소스 관리, Context - 명령
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;
	ComPtr<IDXGISwapChain> SwapChain;

	//Resources
	ComPtr<ID3D11Texture2D> BackBufferTexture;
	ComPtr<ID3D11RenderTargetView> RTV;

	ComPtr<ID3D11RasterizerState> RasterizerState;
	D3D11_VIEWPORT Viewport;

	FColor ClearColor = FColor::WHITE;
};
