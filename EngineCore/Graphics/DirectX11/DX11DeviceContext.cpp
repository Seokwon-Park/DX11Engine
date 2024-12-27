#include "EnginePCH.h"
#include "DX11DeviceContext.h"
#include <EngineBase/EngineMath.h>

DX11DeviceContext::DX11DeviceContext()
{
}

DX11DeviceContext::~DX11DeviceContext()
{

	int a = 0;
	
	
	RTV=nullptr;
	RasterizerState=nullptr;
	BackBufferTexture=nullptr;
	SwapChain=nullptr;
	Context=nullptr;
#if defined(DEBUG) || defined(_DEBUG)
	Microsoft::WRL::ComPtr<ID3D11Debug> DXGIDebug;

	if (SUCCEEDED(Device->QueryInterface(IID_PPV_ARGS(&DXGIDebug))))
	{
		DXGIDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL);
		DXGIDebug = nullptr;
	}
#endif
	Device=nullptr;
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
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN Adapter로 찾아서 사용할 때
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE Default Adapter를 사용할때
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE ?
	// 
	//HMODULE Software, // 특정 단계용(랜더링 파이프라인의 일부를 내가 만든 코드로 교체하기 위한 dll 핸들)
	//UINT Flags, // 옵션

	// _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	// UINT FeatureLevels, //FeatuerLevels 크기
	// UINT SDKVersion, // DirectSDK버전.
	// _COM_Outptr_opt_ ID3D11Device** ppDevice, // 디바이스 주소
	// _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
	// _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

	D3D_FEATURE_LEVEL ResultLevel;
	ComPtr<ID3D11Device> ResultDevice;
	ComPtr<ID3D11DeviceContext> ResultContext;

	if (FAILED(D3D11CreateDevice(
		Adapter.Get(),
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr, // 특정 단계를 내가 짠 코드로 대체
		DeviceFlag,
		nullptr, // 강제레벨 지정 11로 만들거니까. 배열을 넣어줄수
		0, // 내가 지정한 feature 레벨 개수
		D3D11_SDK_VERSION, // 현재 다이렉트x sdk 버전
		&ResultDevice,
		&ResultLevel,
		&ResultContext)))
	{
		MSGASSERT("그래픽 디바이스 생성에 실패했습니다.");
	}

	ResultDevice.As(&Device);
	ResultContext.As(&Context);

	if (ResultLevel != D3D_FEATURE_LEVEL_11_0
		&& ResultLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MSGASSERT("다이렉트 11버전을 지원하지 않는 그래픽카드 입니다.");
		return;
	}

	// 다이렉트 x가 기본적으로 쓰레드 안정성을 안챙겨준다.
	// 고급 랜더링과 서버에서는 쓰레드는 필수이기 때문에
	// 쓰레드를 사용하겠다는 것을 미리 명시해줄수 있다.
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MSGASSERT("스레드 초기화에 실패했습니다.");
	}

	CreateSwapChain(_Window);
	CreateRasterizer();
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
	FactoryPtr->Release();
	Adapter->Release();

	if (nullptr == SwapChain)
	{
		MSGASSERT("스왑체인 제작에 실패했습니다.");
	}

	BackBufferTexture = nullptr;
	if (FAILED(SwapChain->GetBuffer(0, IID_PPV_ARGS(BackBufferTexture.GetAddressOf()))))
	{
		MSGASSERT("백버퍼 텍스처를 얻어오는데 실패했습니다.");
	}

	if (FAILED(Device->CreateRenderTargetView(BackBufferTexture.Get(), nullptr, RTV.GetAddressOf())))
	{
		MSGASSERT("텍스처 수정권한 획득에 실패했습니다");
	}

}

void DX11DeviceContext::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_RASTERIZER_DESC));

	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
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

void DX11DeviceContext::DrawCall()
{
	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV.Get(); // SV_Target0

	Context->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->DrawIndexed(6, 0, 0);
}



IDXGIAdapter* DX11DeviceContext::GetHighPerFormanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(IID_PPV_ARGS(&Factory));

	if (nullptr == Factory)
	{
		MSGASSERT("그래픽카드 조사용 팩토리 생성에 실패했습니다.");
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
		MSGASSERT("그래픽카드를 찾을 수 없습니다.");
		return nullptr;
	}

	return Adapter;
}




void DX11DeviceContext::ClearRenderTarget()
{
	// 이미지 ClearColor으로 렌더타겟 초기화
	Context->ClearRenderTargetView(RTV.Get(), ClearColor.V);
}


void DX11DeviceContext::SwapBuffers()
{
	// 내가 지정한 hwnd에 다이렉트 랜더링 결과를 출력해라.
	HRESULT Result = SwapChain->Present(0, 0);

	//             디바이스가 랜더링 도중 삭제          디바이스가 리셋되었을경우
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MSGASSERT("해상도 변경이나 디바이스 관련 설정이 런타임 도중 수정되었습니다");
		return;
	}
}



