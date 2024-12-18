#include "EnginePCH.h"
#include "DX11DeviceContext.h"
#include <EngineBase/EngineMath.h>

DX11DeviceContext::DX11DeviceContext()
{
}

DX11DeviceContext::~DX11DeviceContext()
{
}

void DX11DeviceContext::Init(const UEngineWindow& _Window)
{
	Adapter = GetHighPerFormanceAdapter();

	UINT DeviceFlag = 0;
#if defined(DEBUG) || defined(_DEBUG)
	DeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//CreateDevice Inputs
	// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice
	//D3D_DRIVER_TYPE DriverType,
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN Adapter�� ã�Ƽ� ����� ��
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE Default Adapter�� ����Ҷ�
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE ?
	// 
	//HMODULE Software, // Ư�� �ܰ��(������ ������������ �Ϻθ� ���� ���� �ڵ�� ��ü�ϱ� ���� dll �ڵ�)
	//UINT Flags, // �ɼ�

	// _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	// UINT FeatureLevels, //FeatuerLevels ũ��
	// UINT SDKVersion, // DirectSDK����.
	// _COM_Outptr_opt_ ID3D11Device** ppDevice, // ����̽� �ּ�
	// _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
	// _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

	D3D_FEATURE_LEVEL ResultLevel;
	ComPtr<ID3D11Device> ResultDevice;
	ComPtr<ID3D11DeviceContext> ResultContext;

	if (FAILED(D3D11CreateDevice(
		Adapter.Get(),
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr, // Ư�� �ܰ踦 ���� § �ڵ�� ��ü
		DeviceFlag,
		nullptr, // �������� ���� 11�� ����Ŵϱ�. �迭�� �־��ټ�
		0, // ���� ������ ��ó���� ����
		D3D11_SDK_VERSION, // ���� ���̷�Ʈx sdk ����
		&ResultDevice,
		&ResultLevel,
		&ResultContext)))
	{
		MSGASSERT("�׷��� ����̽� ������ �����߽��ϴ�.");
	}

	ResultDevice.As(&Device);
	ResultContext.As(&Context);

	if (ResultLevel != D3D_FEATURE_LEVEL_11_0
		&& ResultLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MSGASSERT("���̷�Ʈ 11������ �������� �ʴ� �׷���ī�� �Դϴ�.");
		return;
	}

	// ���̷�Ʈ x�� �⺻������ ������ �������� ��ì���ش�.
	// ��� �������� ���������� ������� �ʼ��̱� ������
	// �����带 ����ϰڴٴ� ���� �̸� ������ټ� �ִ�.
	// Com���̺귯�� �ʱ�ȭ
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MSGASSERT("������ �ʱ�ȭ�� �����߽��ϴ�.")
	}

	CreateSwapChain(_Window);
}
void DX11DeviceContext::CreateSwapChain(const UEngineWindow& _Window)
{
	FIntPoint WindowSize = _Window.GetWindowSize();

	DXGI_SWAP_CHAIN_DESC SwapChinDesc = { 0 };

	SwapChinDesc.BufferCount = 2;
	SwapChinDesc.BufferDesc.Width = WindowSize.X;
	SwapChinDesc.BufferDesc.Height = WindowSize.Y;
	SwapChinDesc.OutputWindow = _Window.GetHandle();
	SwapChinDesc.Windowed = true;

	SwapChinDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChinDesc.BufferDesc.RefreshRate.Numerator = 60;

	SwapChinDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ����ͳ� �����쿡 �ȼ��� ���ŵǴ� ������ ��� 
	// �׳� ���� �����ɷ� ����
	SwapChinDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// ��¥ ���ȳ� �ƿ� 
	SwapChinDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChinDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	//MSAA Sampling
	SwapChinDesc.SampleDesc.Quality = 0;
	// �� ������ 1���� ����ϴ�.
	SwapChinDesc.SampleDesc.Count = 1;

	// ���� n�� �������?
	// n���� ���ۿ� ���� 
	SwapChinDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// ���� ���ȳ�
	SwapChinDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGIFactory* pF = nullptr;

	// �� ���� ���丮�� ���ü� �ִ�.
	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

	// IUnknown* pDevice,
	// DXGI_SWAP_CHAIN_DESC* pDesc,
	// IDXGISwapChain** ppSwapChain

	pF->CreateSwapChain(Device.Get(), &SwapChinDesc, SwapChain.GetAddressOf());

	pF->Release();
	Adapter->Release();

	if (nullptr == SwapChain)
	{
		MSGASSERT("����ü�� ���ۿ� �����߽��ϴ�.");
	}

	BackBufferTexture = nullptr;
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>
		(BackBufferTexture.GetAddressOf())))
	{
		MSGASSERT("����� �ؽ�ó�� �����µ� �����߽��ϴ�.");
	};

	// id3d11texture2d* �̳༮ �����δ� �Ҽ� �ִ°� ���� �����ϴ�.
	// �ִ� �̹����� 2���� �����͸� ��Ÿ���� ���������� ���� �����Դϴ�.
	// �̹����� �����ϰų� ����Ҽ� �ִ� ������ id3d11texture2d*�� ���� �մϴ�.
	// WINAPI���� HDC ���� ��ó�� id3d11texture2d* ����������
	// �ؽ�ó���� ������ �մϴ�.

	//                             HBITMAP                       HDC
	if (S_OK != Device->CreateRenderTargetView(BackBufferTexture.Get(), nullptr, &RTV))
	{
		MSGASSERT("�ؽ�ó �������� ȹ�濡 �����߽��ϴ�");
	}

}

IDXGIAdapter* DX11DeviceContext::GetHighPerFormanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MSGASSERT("�׷���ī�� ����� ���丮 ������ �����߽��ϴ�.");
		return nullptr;
	}

	for (int Index = 0;; ++Index)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		Adapter = CurAdapter;
	}

	if (nullptr != Factory)
	{
		Factory->Release();
	}

	if (nullptr == Adapter)
	{
		MSGASSERT("�׷���ī�带 ã�� �� �����ϴ�.");
		return nullptr;
	}

	return Adapter;
}

void DX11DeviceContext::ClearRenderTarget()
{
	// �̹��� ClearColor���� ����Ÿ�� �ʱ�ȭ
	Context->ClearRenderTargetView(RTV.Get(), ClearColor.V);
}


void DX11DeviceContext::SwapBuffers()
{
	// ���� ������ hwnd�� ���̷�Ʈ ������ ����� ����ض�.
	HRESULT Result = SwapChain->Present(0, 0);

	//             ����̽��� ������ ���� ����          ����̽��� ���µǾ������
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MSGASSERT("�ػ� �����̳� ����̽� ���� ������ ��Ÿ�� ���� �����Ǿ����ϴ�");
		return;
	}
}



