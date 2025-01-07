#include "EnginePCH.h"
#include "ResourceManager.h"
#include "EngineShaderFactory.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineMesh.h>
#include <EngineCore/Resources/EngineMaterial.h>

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
}

void UResourceManager::CreateDefaultResources()
{
	CreateDefaultShader();
	CreateDefaultVertexBuffer();
	CreateDefaultInputLayout();
	CreateDefaultIndexBuffer();
	CreateDefaultMesh();
	CreateDefaultMaterial();
}

void UResourceManager::CreateDefaultVertexBuffer()
{
	std::vector<Vertex> Vertices;

	Vertices.resize(4);

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, 1.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, 1.0f,1.0f), {0.0f, 1.0f, 0.0f, 1.0f}	,{1.0f, 0.0f} };
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, 1.0f,1.0f), {0.0f, 0.0f, 1.0f, 1.0f},{0.0f, 1.0f} };
	Vertices[3] = Vertex{ FVector4(0.5f, -0.5f, 1.0f,1.0f), {1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f} };

	Uint32 DataSize = static_cast<Uint32>(sizeof(Vertex) * Vertices.size());
	Uint32 VertexCount = static_cast<Uint32>(Vertices.size());

	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Quad", 
		Vertices.data(), DataSize, VertexCount);
}

void UResourceManager::CreateDefaultInputLayout()
{
	std::vector<FInputLayoutElement> InputLayoutElements =
	{
	{ EInputLayoutDataType::Float4, "POSITION" },
	{ EInputLayoutDataType::Float4, "COLOR" },
	{ EInputLayoutDataType::Float2, "TEXCOORD" },
	};

	std::shared_ptr<UEngineShader> VertexShader = Find<UEngineShader>("QuadVS");

	std::shared_ptr<UEngineInputLayout> InputLayout = UEngineInputLayout::Create(VertexShader, InputLayoutElements);
	AddResource<UEngineInputLayout>(InputLayout, "Quad", "");
}

void UResourceManager::CreateDefaultIndexBuffer()
{
	std::vector<Uint32> Indices = { 0,1,2,1,3,2 };
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create(&Indices[0], 6);
	AddResource<UEngineIndexBuffer>(IndexBuffer, "Quad", "");
}

void UResourceManager::CreateDefaultMesh()
{
	std::shared_ptr<UEngineMesh> Mesh = UEngineMesh::Create("Quad", "Quad", "Quad");
	AddResource<UEngineMesh>(Mesh, "Quad", "");
}

void UResourceManager::CreateDefaultMaterial()
{
	std::shared_ptr<UEngineMaterial> Material = UEngineMaterial::Create();
	AddResource<UEngineMaterial>(Material, "Quad", "");

}

void UResourceManager::CreateDefaultShader()
{
	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("EngineCore");
	Dir.AppendDirectory("Shaders");
	std::vector<UEngineFile> Files = Dir.GetAllFile(false, { ".hlsl" });
	const type_info& Info = typeid(UEngineShader);
	for (UEngineFile File : Files)
	{
		std::shared_ptr<UEngineShader> VertexShader = UEngineShaderFactory::Create(File.ToString(), EShaderType::VS);
		std::shared_ptr<UEngineShader> PixelShader = UEngineShaderFactory::Create(File.ToString(), EShaderType::PS);
		AddResource(VertexShader, Info.name(), "QuadVS", Dir.ToString());
		AddResource(PixelShader, Info.name(), "QuadPS", Dir.ToString());
	}
	
}
