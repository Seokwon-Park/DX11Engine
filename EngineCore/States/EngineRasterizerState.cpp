#include "EnginePCH.h"
#include "EngineRasterizerState.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineDeviceContext.h>


UEngineRasterizerState::UEngineRasterizerState()
{
}

UEngineRasterizerState::~UEngineRasterizerState()
{
}

void UEngineRasterizerState::Bind()
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->RSSetState(RasterizerState.Get());
}

ENGINE_API std::shared_ptr<UEngineRasterizerState> UEngineRasterizerState::Create(std::string_view _Name)
{
	D3D11_RASTERIZER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_RASTERIZER_DESC));
	Desc.FillMode = D3D11_FILL_SOLID;
	Desc.CullMode = D3D11_CULL_NONE;
	//Desc.FrontCounterClockwise;
	//Desc.DepthBias = 1;
	//Desc.DepthBiasClamp =0.0f;
	//Desc.SlopeScaledDepthBias= 0.1f;
	//Desc.DepthClipEnable;
	//Desc.ScissorEnable;
	//Desc.MultisampleEnable;
	//Desc.AntialiasedLineEnable;
	return Create(_Name, Desc);
}

ENGINE_API std::shared_ptr<UEngineRasterizerState> UEngineRasterizerState::Create(std::string_view _Name,const D3D11_RASTERIZER_DESC& _Desc)
{
	std::shared_ptr<UEngineRasterizerState> RasterizerState = std::make_shared<UEngineRasterizerState>();
	RasterizerState->CreateRasterizerState(_Desc);
	UStateManager::AddState<UEngineRasterizerState>(RasterizerState, _Name);
	return RasterizerState;
}

void UEngineRasterizerState::CreateRasterizerState(D3D11_RASTERIZER_DESC _Desc)
{
	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateRasterizerState(&_Desc, RasterizerState.GetAddressOf());
}
