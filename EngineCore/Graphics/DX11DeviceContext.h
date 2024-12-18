#pragma once

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

// ���� :
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

	// Adapter �׷���ī���� ������ ������ �ִ� �������̽�
	IDXGIAdapter* GetHighPerFormanceAdapter();
protected:

private:
	ComPtr<IDXGIAdapter> Adapter = nullptr;
	// Device - ���ҽ� ����, Context - ���
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;

	ComPtr<IDXGISwapChain> SwapChain;

	//Resources
	ComPtr<ID3D11Texture2D> BackBufferTexture = nullptr;
	ComPtr<ID3D11RenderTargetView> RTV = nullptr;

};

