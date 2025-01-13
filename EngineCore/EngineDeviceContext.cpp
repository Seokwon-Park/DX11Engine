#include "EnginePCH.h"
#include "EngineDeviceContext.h"
#include <EngineCore/Resources/EngineTexture.h>


UEngineDeviceContext::UEngineDeviceContext()
{

}

UEngineDeviceContext::~UEngineDeviceContext()
{
	// ���� Ÿ��, ���� ���ٽ� �ؽ��Ĵ� ������ ���⼭ ���������.
	RenderTargetTextures.clear();
	DepthStencilTexture = nullptr;
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

void UEngineDeviceContext::CreateBackBuffer(const UEngineWindow& _Window)
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

	//����� ����
	BackBufferTexture = std::make_shared<UEngineTexture2D>();
	if (FAILED(SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBufferTexture->GetTextureRef()))))
	{
		MSGASSERT("����� �ؽ�ó�� �����µ� �����߽��ϴ�.");
	}
	BackBufferTexture->CreateRTV();
	RenderTargetTextures.push_back(BackBufferTexture);

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_TEXTURE2D_DESC));
	Desc.Width = WindowSize.X;
	Desc.Height = WindowSize.Y;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;

	DepthStencilTexture = UEngineTexture2D::Create("DepthStencil", Desc);
	//DepthStencilTexture->CreateDSV();
	//������ �ʿ��ϴ�.
	SetViewport(0.0f, 0.0f, (float)WindowSize.X, (float)WindowSize.Y);

}

void UEngineDeviceContext::SetViewport(float _TopLeftX, float _TopLeftY, float _Width, float _Height, float _MinDepth, float _MaxDepth)
{
	Viewport.TopLeftX = _TopLeftX;
	Viewport.TopLeftY = _TopLeftY;
	Viewport.Width = _Width;
	Viewport.Height = _Height;
	Viewport.MinDepth = _MinDepth;
	Viewport.MaxDepth = _MaxDepth;

	Context->RSSetViewports(1, &Viewport);
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
	int Index = 0;
	while(true)
	{
		Index++;
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

void UEngineDeviceContext::Clear()
{
	// �̹��� ClearColor���� ����Ÿ�� �ʱ�ȭ
	std::vector<ID3D11RenderTargetView*> RenderTargetViewArray;

	for (std::shared_ptr<UEngineTexture2D>& RenderTargetTexture : RenderTargetTextures)
	{
		RenderTargetViewArray.push_back(RenderTargetTexture->GetRTV());
		Context->ClearDepthStencilView(DepthStencilTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		Context->ClearRenderTargetView(RenderTargetTexture->GetRTV(), ClearColor.V);
	}
	Context->OMSetRenderTargets(1, RenderTargetViewArray.data(), DepthStencilTexture->GetDSV());
}


void UEngineDeviceContext::SwapBuffers()
{
	HRESULT Result = SwapChain->Present(1, 0);

	//             ����̽��� ������ ���� ����          ����̽��� ���µǾ������
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MSGASSERT("�ػ� �����̳� ����̽� ���� ������ ��Ÿ�� ���� �����Ǿ����ϴ�");
		return;
	}
}




