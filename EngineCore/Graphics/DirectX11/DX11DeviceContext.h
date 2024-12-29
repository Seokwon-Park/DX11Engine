#pragma once

#define ReleaseCOM(X) if(X != nullptr)		\
					{ X->Release(); }   \
// 설명 :
class DX11DeviceContext : public UEngineDeviceContext
{
public:
	// constrcuter destructer
	ENGINE_API DX11DeviceContext();
	ENGINE_API ~DX11DeviceContext();

	// delete Function
	DX11DeviceContext(const DX11DeviceContext& _Other) = delete;
	DX11DeviceContext(DX11DeviceContext&& _Other) noexcept = delete;
	DX11DeviceContext& operator=(const DX11DeviceContext& _Other) = delete;
	DX11DeviceContext& operator=(DX11DeviceContext&& _Other) noexcept = delete;

	virtual void Init(const UEngineWindow& _Window)override;
	virtual void ClearRenderTarget()override;
	virtual void SwapBuffers()override;
	virtual void CreateBackBuffer(const UEngineWindow& _Window) override;

	void CreateSwapChain(const UEngineWindow& _Window);
	void CreateRasterizer();
	void DrawCall();
	ID3D11Device* GetDevice() const { return Device.Get(); }
	ID3D11DeviceContext* GetContext() const { return Context.Get(); }

	// Adapter 그래픽카드의 정보를 가지고 있는 인터페이스
	IDXGIAdapter* GetHighPerFormanceAdapter();
protected:

private:
	ComPtr<IDXGIAdapter> Adapter = nullptr;
	// Device - 리소스 관리, Context - 명령
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;

	ComPtr<IDXGISwapChain> SwapChain;

	//Resources
	ComPtr<ID3D11Texture2D> BackBufferTexture = nullptr;
	ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	D3D11_VIEWPORT Viewport;



	// Inherited via UEngineDeviceContext




};

