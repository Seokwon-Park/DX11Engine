#include "EnginePCH.h"
#include "RendererComponent.h"
#include "Graphics/EngineBuffer.h"
#include "Graphics/EngineShader.h"
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

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, -0.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, -0.0f,1.0f), {0.0f, 1.0f, 0.0f, 1.0f} };
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, -0.0f,1.0f), {0.0f, 0.0f, 1.0f, 1.0f} };
	Vertices[3] = Vertex{ FVector4(0.5f, -0.5f, -0.0f,1.0f), {1.0f, 1.0f, 1.0f, 1.0f} };

	Test = VertexBuffer::Create(Vertices, sizeof(Vertex) * Vertices.size(), Vertices.size());
	Test2 = IndexBuffer::Create(Indices, 6);
	Test3 = EngineShader::Create("");

}

void URendererComponent::Render(float _DeltaTime)
{
	Test->Bind();
	Test2->Bind();
	Test3->Bind();
	UEngineCore::GraphicsDevice->DrawCall();
	
}
