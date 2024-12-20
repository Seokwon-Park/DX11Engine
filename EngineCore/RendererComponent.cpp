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
<<<<<<< HEAD
	Test->Bind();
	Test2->Bind();
	Test3->Bind();
	UEngineCore::GraphicsDevice->DrawCall();
	
=======
	std::vector<Vertex> Vertices;
	Vertices.resize(6);

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, -0.5f), {} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, -0.5f), {} };
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, -0.5f), {} };
	Vertices[3] = Vertex{ FVector4(0.5f, 0.5f, -0.5f), {} };
	Vertices[4] = Vertex{ FVector4(0.5f, -0.5f, -0.5f), {} };
	Vertices[5] = Vertex{ FVector4(-0.5f, -0.5f, -0.5f), {} };
	std::shared_ptr<VertexBuffer> Buffer = VertexBuffer::Create(Vertices, sizeof(Vertex)*6, 6);
	Buffer->Bind();
	std::shared_ptr<EngineShader> Shader = EngineShader::Create("");
	Shader->Bind();
>>>>>>> 59ac2f97383e839d272725f1a70258eafd232c81
}
