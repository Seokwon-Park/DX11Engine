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
#include <EngineCore/States/EngineSamplerState.h>


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
	//auto test = UEngineSamplerState::Create();
	//test->Bind(EShaderType::PS, 0);
}

void URendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	UEngineCore::GetGraphicsDeviceContext()->DrawCall();

	for (std::shared_ptr<URenderUnit> RenderUnit : RenderUnits)
	{
		RenderUnit->Render(_Camera, _DeltaTime);
	}

}
