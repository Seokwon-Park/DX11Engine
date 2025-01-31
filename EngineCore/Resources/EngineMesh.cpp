#include "EnginePCH.h"
#include "EngineMesh.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>

UEngineMesh::UEngineMesh()
{
}

UEngineMesh::~UEngineMesh()
{
}

std::shared_ptr<UEngineMesh> UEngineMesh::Create(std::string_view _Name, std::string_view _VBName, std::string_view _IBName, D3D_PRIMITIVE_TOPOLOGY _PrimitiveTopology)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	std::shared_ptr<UEngineMesh> NewMesh = std::make_shared<UEngineMesh>();
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UResourceManager::Find<UEngineVertexBuffer>(_VBName);
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UResourceManager::Find<UEngineIndexBuffer>(_IBName);
	NewMesh->VertexBuffer = VertexBuffer;
	NewMesh->IndexBuffer = IndexBuffer;
	NewMesh->PrimitiveTopology = _PrimitiveTopology;

	UResourceManager::AddResource<UEngineMesh>(NewMesh, _Name, "");

	return NewMesh;
}

void UEngineMesh::Bind() const
{
	VertexBuffer->Bind();
	IndexBuffer->Bind();
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->IASetPrimitiveTopology(PrimitiveTopology);
}

