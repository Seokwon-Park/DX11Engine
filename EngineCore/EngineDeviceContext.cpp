#include "EnginePCH.h"
#include "EngineDeviceContext.h"

UEngineDeviceContext::UEngineDeviceContext()
{

}

UEngineDeviceContext::~UEngineDeviceContext()
{
	RenderTargetView = nullptr;
	RasterizerState = nullptr;
	BackBufferTexture = nullptr;
	SwapChain = nullptr;
	Context = nullptr;
#if defined(DEBUG) || defined(_DEBUG)
	Microsoft::WRL::ComPtr<ID3D11Debug> DXGIDebug;

	if (SUCCEEDED(Device->QueryInterface(IID_PPV_ARGS(&DXGIDebug))))
	{
		DXGIDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL);
		DXGIDebug = nullptr;
	}
#endif
	Device = nullptr;
}

void UEngineDeviceContext::Init(const UEngineWindow& _Window)
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

	if (FAILED(D3D11CreateDevice(
		Adapter.Get(),
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr, // Ư�� �ܰ踦 ���� § �ڵ�� ��ü
		DeviceFlag,
		nullptr, // �������� ���� 11�� ����Ŵϱ�. �迭�� �־��ټ�
		0, // ���� ������ feature ���� ����
		D3D11_SDK_VERSION, // ���� ���̷�Ʈx sdk ����
		Device.GetAddressOf(),
		&ResultLevel,
		Context.GetAddressOf())))
	{
		MSGASSERT("�׷��� ����̽� ������ �����߽��ϴ�.");
	}

	if (ResultLevel != D3D_FEATURE_LEVEL_11_0
		&& ResultLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MSGASSERT("���̷�Ʈ 11������ �������� �ʴ� �׷���ī���Դϴ�.");
		return;
	}

	// ���̷�Ʈ x�� �⺻������ ������ �������� ��ì���ش�.
	// ��� �������� ���������� ������� �ʼ��̱� ������
	// �����带 ����ϰڴٴ� ���� �̸� ������ټ� �ִ�.
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MSGASSERT("������ �ʱ�ȭ�� �����߽��ϴ�.");
	}
}

void UEngineDeviceContext::CreateSwapChain(const UEngineWindow& _Window)
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
	SwapChinDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChinDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChinDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	SwapChinDesc.SampleDesc.Quality = 0;
	SwapChinDesc.SampleDesc.Count = 1;

	SwapChinDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChinDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGIFactory* FactoryPtr = nullptr;

	Adapter->GetParent(IID_PPV_ARGS(&FactoryPtr));

	FactoryPtr->CreateSwapChain(Device.Get(), &SwapChinDesc, SwapChain.GetAddressOf());

	if (nullptr == SwapChain)
	{
		MSGASSERT("����ü�� ������ �����߽��ϴ�.");
	}

	if (FAILED(SwapChain->GetBuffer(0, IID_PPV_ARGS(BackBufferTexture.GetAddressOf()))))
	{
		MSGASSERT("����� �ؽ�ó�� �����µ� �����߽��ϴ�.");
	}

	if (FAILED(Device->CreateRenderTargetView(BackBufferTexture.Get(), nullptr, RenderTargetView.GetAddressOf())))
	{
		MSGASSERT("�ؽ�ó �������� ȹ�濡 �����߽��ϴ�");
	}

}

void UEngineDeviceContext::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_RASTERIZER_DESC));

	Desc.FillMode = D3D11_FILL_SOLID;
	Desc.CullMode = D3D11_CULL_BACK;
	//Desc.FrontCounterClockwise;
	//Desc.DepthBias;
	//Desc.DepthBiasClamp;
	//Desc.SlopeScaledDepthBias;
	//Desc.DepthClipEnable;
	//Desc.ScissorEnable;
	//Desc.MultisampleEnable;
	//Desc.AntialiasedLineEnable;

	Device.Get()->CreateRasterizerState(&Desc, RasterizerState.GetAddressOf());

	Viewport.Height = 720.0f;
	Viewport.Width = 1280.0f;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &Viewport);
	Context->RSSetState(RasterizerState.Get());
}

void UEngineDeviceContext::DrawCall()
{
	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RenderTargetView.Get(); // SV_Target0

	Context->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}

IDXGIAdapter* UEngineDeviceContext::GetHighPerFormanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(IID_PPV_ARGS(&Factory));

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

void UEngineDeviceContext::ClearRenderTarget()
{
	// �̹��� ClearColor���� ����Ÿ�� �ʱ�ȭ
	//Context->ClearDepthStencilView(DepthStencilView.Get());
	Context->ClearRenderTargetView(RenderTargetView.Get(), ClearColor.V);
}


void UEngineDeviceContext::SwapBuffers()
{
	HRESULT Result = SwapChain->Present(0, 0);

	//             ����̽��� ������ ���� ����          ����̽��� ���µǾ������
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MSGASSERT("�ػ� �����̳� ����̽� ���� ������ ��Ÿ�� ���� �����Ǿ����ϴ�");
		return;
	}
}

void UEngineDeviceContext::CreateBackBuffer(const UEngineWindow& _Window)
{
	CreateSwapChain(_Window);
	CreateRasterizer();
}


