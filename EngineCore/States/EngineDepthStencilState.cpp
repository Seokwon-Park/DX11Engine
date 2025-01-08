#include "EnginePCH.h"
#include "EngineDepthStencilState.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineDeviceContext.h>

UEngineDepthStencilState::UEngineDepthStencilState()
{
}

UEngineDepthStencilState::~UEngineDepthStencilState()
{
}

void UEngineDepthStencilState::Bind()
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->OMSetDepthStencilState(DepthStencilState.Get(), 0);
}

std::shared_ptr<UEngineDepthStencilState> UEngineDepthStencilState::Create(std::string_view _Name)
{
	D3D11_DEPTH_STENCIL_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	Desc.DepthEnable = false;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	Desc.StencilEnable = false;
	//Desc.StencilReadMask;
	//Desc.StencilWriteMask;
	//Desc.FrontFace;
	//Desc.BackFace;
	return Create(_Name, Desc);
}

std::shared_ptr<UEngineDepthStencilState> UEngineDepthStencilState::Create(std::string_view _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	std::shared_ptr<UEngineDepthStencilState> NewDepthStencilState = std::make_shared<UEngineDepthStencilState>();
	NewDepthStencilState->CreateDepthStencilState(_Desc);
	UStateManager::AddState<UEngineDepthStencilState>(NewDepthStencilState, _Name);
	return NewDepthStencilState;
}

void UEngineDepthStencilState::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC _Desc)
{
	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateDepthStencilState(&_Desc, DepthStencilState.GetAddressOf());
}
