#include "EnginePCH.h"
#include "RendererComponent.h"
#include "CameraComponent.h"

#include <EngineCore/Actor.h>
#include "ResourceManager.h"
#include "EngineDeviceContext.h"
#include <EngineShaderFactory.h>
#include <EngineCore/Resources/EngineMesh.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineCore/Resources/EngineSamplerState.h>


URendererComponent::URendererComponent()
{
}

URendererComponent::~URendererComponent()
{
}

void URendererComponent::BeginPlay()
{
	auto Mesh = UResourceManager::Find<UEngineMesh>("Quad");
	Mesh->Bind();
	VS = UResourceManager::Find<UEngineShader>("QuadVS");
	PS = UResourceManager::Find<UEngineShader>("QuadPS");
	VS->Bind();
	PS->Bind();
	std::shared_ptr<UEngineInputLayout> IL = UResourceManager::Find<UEngineInputLayout>("Quad");
	IL->Bind();

	auto test = UEngineSamplerState::Create();
	test->Bind();
}

void URendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View.MatrixView(FVector4::BACK, FVector4::FORWARD, FVector4::UP);
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj.MatrixOrthoLH(1280.f, 720.0f, 0.01f, 100.0f);
	VC.Proj.MatrixTranspose();
	//Test2->Bind();
	//Test3->Bind();
	//Shader->SetVertexConstants(Data);
	std::shared_ptr<UEngineConstantBuffer> Test = UEngineConstantBuffer::Create(VC);
	Test->Bind(EShaderType::VS, 0);

	for (URenderUnit* RenderUnit : RenderUnits)
	{
		RenderUnit->Render(_Camera, _DeltaTime);
	}


	UEngineCore::GraphicsDeviceContext->DrawCall();
}
