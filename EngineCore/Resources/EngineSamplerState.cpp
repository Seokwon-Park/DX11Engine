#include "EnginePCH.h"
#include "EngineSamplerState.h"
#include "EngineDeviceContext.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/ResourceManager.h>

UEngineSamplerState::UEngineSamplerState()
{
}

UEngineSamplerState::~UEngineSamplerState()
{
}

std::shared_ptr<UEngineSamplerState> UEngineSamplerState::Create(std::string_view _Name)
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

	return Create(_Name, SamplerDesc);
}

std::shared_ptr<UEngineSamplerState> UEngineSamplerState::Create(std::string_view _Name, D3D11_SAMPLER_DESC _Desc)
{
	std::shared_ptr<UEngineSamplerState> NewSampler = std::make_shared<UEngineSamplerState>();
	NewSampler->CreateSamplerState(_Desc);
	UResourceManager::AddResource<UEngineSamplerState>(NewSampler, _Name, "");
	return NewSampler;
}

void UEngineSamplerState::CreateSamplerState(D3D11_SAMPLER_DESC _Desc)
{
	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateSamplerState(&_Desc, SamplerState.GetAddressOf());
}

void UEngineSamplerState::Bind(EShaderType _Type, Uint32 Slot) const
{
	switch (_Type)
	{
	case EShaderType::VS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->VSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	case EShaderType::HS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->HSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	case EShaderType::DS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->DSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	case EShaderType::GS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->GSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	case EShaderType::PS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->PSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	case EShaderType::CS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->CSSetSamplers(Slot, 1, SamplerState.GetAddressOf());
		break;
	default:
		break;
	}
}

