#include "EnginePCH.h"
#include "RendererComponent.h"
#include "Graphics/EngineBuffer.h"
#include "Graphics/EngineShader.h"
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
}

void URendererComponent::Render(float _DeltaTime)
{
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
}
