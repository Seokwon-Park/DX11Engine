#include "EnginePCH.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineMesh.h>

std::map<std::string, std::map<std::string, std::shared_ptr<UEngineResource>>> UResourceManager::ResourceMap;

UResourceManager::UResourceManager()
{
}

UResourceManager::~UResourceManager()
{
}

std::shared_ptr<UEngineResource> UResourceManager::Find(std::string_view _ResourceType, std::string_view _ResourceName)
{
	std::string UpperString = UEngineString::ToUpper(_ResourceName);

	if (false == ResourceMap[_ResourceType.data()].contains(UpperString))
	{
		return nullptr;
	}

	return ResourceMap[_ResourceType.data()][UpperString];
}

void UResourceManager::AddResource(std::shared_ptr<UEngineResource> _Resource, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	if (true == ResourceMap[_Info.data()].contains(_Name.data()))
	{
		MSGASSERT("이미 추가한 리소스를 또 추가하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_Name);

	_Resource->SetName(UpperName);
	_Resource->SetPath(_Path);
	ResourceMap[_Info.data()].insert(std::make_pair(UpperName, _Resource));

	return;
}

void UResourceManager::CreateDefaultResources()
{
	CreateBaseVertexBuffer();
}

void UResourceManager::CreateBaseVertexBuffer()
{
	std::vector<Vertex> Vertices;

	Vertices.resize(4);

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, 1.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, 1.0f,1.0f), {0.0f, 1.0f, 0.0f, 1.0f}	,{1.0f, 0.0f} };
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, 1.0f,1.0f), {0.0f, 0.0f, 1.0f, 1.0f},{0.0f, 1.0f} };
	Vertices[3] = Vertex{ FVector4(0.5f, -0.5f, 1.0f,1.0f), {1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f} };

	Uint32 DataSize = static_cast<Uint32>(sizeof(Vertex) * Vertices.size());
	Uint32 VertexCount = static_cast<Uint32>(Vertices.size());

	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create(
		reinterpret_cast<void*>(&Vertices[0]), DataSize, VertexCount);
	const type_info& Info = typeid(UEngineVertexBuffer);
	AddResource(VertexBuffer, Info.name(), "Quad", "NoPath");
}

void UResourceManager::CreateBaseIndexBuffer()
{
	std::vector<Uint32> Indices = { 0,1,2,1,3,2 };
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create(&Indices[0], 6);
	const type_info& Info = typeid(UEngineVertexBuffer);
	AddResource(IndexBuffer, Info.name(), "Quad", "NoPath");
}

void UResourceManager::CreateBaseMesh()
{
	std::shared_ptr<UEngineMesh> Mesh = UEngineMesh::Create("Quad", "Quad", "Quad");
	const type_info& Info = typeid(UEngineVertexBuffer);
	AddResource(Mesh, Info.name(), "Quad", "NoPath");
}
