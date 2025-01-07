#include "EnginePCH.h"
#include "RendererComponent.h"
#include "CameraComponent.h"

#include <EngineCore/Actor.h>
#include "ResourceManager.h"
#include "EngineDeviceContext.h"
#include <EngineShaderFactory.h>
#include <EngineCore/Resources/EngineMesh.h>
#include <EngineCore/Resources/EngineMaterial.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineCore/Resources/EngineSamplerState.h>
#include <EngineCore/States/EngineBlendState.h>
#include <EngineCore/States/EngineRasterizerState.h>
#include <EngineCore/States/EngineDepthStencilState.h>


URendererComponent::URendererComponent()
{
}

URendererComponent::~URendererComponent()
{
}

std::shared_ptr<URenderUnit> URendererComponent::AddRenderUnit()
{
	std::shared_ptr<URenderUnit> RenderUnit = std::make_shared<URenderUnit>();
	RenderUnits.emplace_back(RenderUnit);
	RenderUnit->SetOwner(this);
	return RenderUnit;
}

void URendererComponent::AddRenderUnit(std::shared_ptr<URenderUnit> _RenderUnit)
{
	RenderUnits.push_back(_RenderUnit);
	_RenderUnit->SetOwner(this);
}

void URendererComponent::BeginPlay()
{

}

void URendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	UEngineBlendState::Create("")->Bind();
	UEngineRasterizerState::Create("")->Bind();
	UEngineDepthStencilState::Create("")->Bind();

	for (std::shared_ptr<URenderUnit> RenderUnit : RenderUnits)
	{
		RenderUnit->Render(_Camera, _DeltaTime);
	}

}
