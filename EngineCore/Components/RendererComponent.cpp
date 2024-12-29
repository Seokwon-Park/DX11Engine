#include "EnginePCH.h"
#include "RendererComponent.h"
#include "Graphics/EngineBuffer.h"
#include "Graphics/EngineShader.h"
#include "Graphics/EngineTexture.h"
#include "ResourceManager.h"
#include "EngineCore.h"
#include "Actor.h"

URendererComponent::URendererComponent()
{
}

URendererComponent::~URendererComponent()
{
}

void URendererComponent::SetOrder(int _Order)
{
}

void URendererComponent::BeginPlay()
{
	GetOwner()->GetLevel()->PushRenderer(GetThis<URendererComponent>());

	std::vector<Vertex> Vertices;
	std::vector<uint32> Indices = { 0,1,2, 1,3,2 };

	Vertices.resize(4);

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, 1.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, 1.0f,1.0f), {0.0f, 1.0f, 0.0f, 1.0f}	,{1.0f, 0.0f}};
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, 1.0f,1.0f), {0.0f, 0.0f, 1.0f, 1.0f},{0.0f, 1.0f}};
	Vertices[3] = Vertex{ FVector4(0.5f, -0.5f, 1.0f,1.0f), {1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}};

	VB = VertexBuffer::Create(Vertices, sizeof(Vertex) * Vertices.size(), Vertices.size());
	VB->Bind();
	IB = IndexBuffer::Create(Indices, 6);
	IB->Bind();
	Shader = UEngineShader::Create("");
	Shader->Bind();
}

void URendererComponent::Render(float _DeltaTime)
{
	VertexConstant Data;
	Data.World = GetTransformRef().WorldMatrix;
	Data.View.MatrixView(FVector4::BACK, FVector4::FORWARD, FVector4::UP);
	Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	Data.Proj.MatrixTranspose();
	//Test2->Bind();
	//Test3->Bind();
	Shader->SetVertexConstants(Data);
	std::shared_ptr<UEngineTexture2D> Test = UResourceManager::Find<UEngineTexture2D>("tevi_n_01.png");
	Test->Bind(0);
	
	UEngineCore::GraphicsDevice->DrawCall();
}
