#include "EnginePCH.h"
#include "EngineBlendState.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineDeviceContext.h>

UEngineBlendState::UEngineBlendState()
{
}

UEngineBlendState::~UEngineBlendState()
{
}

void UEngineBlendState::Bind()
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->OMSetBlendState(BlendState.Get(), UEngineCore::GetGraphicsDeviceContext()->GetClearColor().V, 0xFFFFFFFF);

}

std::shared_ptr<UEngineBlendState> UEngineBlendState::Create(std::string_view _Name)
{
	D3D11_BLEND_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BLEND_DESC));
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = true;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	return Create(_Name, Desc);
}

std::shared_ptr<UEngineBlendState> UEngineBlendState::Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc)
{
	std::shared_ptr<UEngineBlendState> NewBlendState = std::make_shared<UEngineBlendState>();
	NewBlendState->CreateBlendState(_Desc);
	UStateManager::AddState<UEngineBlendState>(NewBlendState, _Name);
	return NewBlendState;
}

void UEngineBlendState::CreateBlendState(D3D11_BLEND_DESC _Desc)
{
	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateBlendState(&_Desc, BlendState.GetAddressOf());
}

