#pragma once

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

	void CreateSwapChain(const UEngineWindow& _Window);
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


	// Inherited via UEngineDeviceContext


};

