#include "EnginePCH.h"
#include "EngineSamplerState.h"
#include <EngineCore/EngineCore.h>

UEngineSamplerState::UEngineSamplerState()
{
}

UEngineSamplerState::~UEngineSamplerState()
{
}

std::shared_ptr<UEngineSamplerState> UEngineSamplerState::Create()
{
	std::shared_ptr<UEngineSamplerState> NewSampler = std::make_shared<UEngineSamplerState>();
	NewSampler->Init();
	return NewSampler;
}

void UEngineSamplerState::Init()
{
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
}

void UEngineSamplerState::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->PSSetSamplers(0, 1, SamplerState.GetAddressOf());
}

