#include "EnginePCH.h"
#include "GridRendererComponent.h"
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

UGridRendererComponent::UGridRendererComponent()
{
}

UGridRendererComponent::~UGridRendererComponent()
{
}

void UGridRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
	GridRenderUnit = AddRenderUnit();
	GridRenderUnit->Init("Quad", "Grid");
	GetOwner()->GetLevel()->PushRenderer(GetThis<UGridRendererComponent>());
}

void UGridRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();
	VC.Proj = _Camera->GetProjectionMatrix();
	VC.Proj.MatrixTranspose();

	auto test = FColor(0.0f, 0.0f, 0.0f, 1.0f);
	GridRenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
	GridRenderUnit->SetConstantBufferData("PSColor", EShaderType::PS, test);

	URendererComponent::Render(_Camera, _DeltaTime);
}

void UGridRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);
}

