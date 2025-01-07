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
	ENGINE_API void SetViewport(float _TopLeftX, float _TopLeftY, float _Width, float _Height, float _MinDepth= 0.0f, float _MaxDepth = 1.0f);

	ENGINE_API inline void SetClearColor(FColor _Color) { ClearColor = _Color; }
	ENGINE_API inline FColor GetClearColor() const { return ClearColor; }
	inline ID3D11Device* GetDevice() const { return Device.Get(); }
	inline ID3D11DeviceContext* GetContext() const { return Context.Get(); }

	IDXGIAdapter* GetHighPerFormanceAdapter();

protected:
	ComPtr<IDXGIAdapter> Adapter = nullptr;
	// Device - 리소스 관리, Context - 명령
	ComPtr<ID3D11Device> Device = nullptr;
	ComPtr<ID3D11DeviceContext> Context = nullptr;
	ComPtr<IDXGISwapChain> SwapChain = nullptr;

	//Resources
	std::shared_ptr<class UEngineTexture2D> BackBufferTexture = nullptr;
	std::shared_ptr<class UEngineTexture2D> DepthStencilTexture = nullptr;

	ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	D3D11_VIEWPORT Viewport;

	FColor ClearColor = FColor::WHITE;
};
