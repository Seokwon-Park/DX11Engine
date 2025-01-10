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
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == ResourceMap[_Info.data()].contains(UpperName))
	{
		MSGASSERT("이미 추가한 리소스를 또 추가하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}


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

	std::shared_ptr<UEngineShader> VertexShader = Find<UEngineShader>("SpriteShaderVS");

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
	UEngineMesh::Create("Quad", "Quad", "Quad", D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void UResourceManager::CreateDefaultMaterial()
{
	UEngineMaterial::Create("Quad");

	FMaterialDescription Desc;
	Desc.VSName = "ColliderShaderVS";
	Desc.PSName = "ColliderShaderPS";
	Desc.InputLayoutName = "Quad";
	Desc.BSName = "Default";
	Desc.RSName = "Wired";
	Desc.DSSName = "Default";
	UEngineMaterial::Create("ColliderDebug", Desc);

	Desc.VSName = "TilemapShaderVS";
	Desc.PSName = "TilemapShaderPS";
	Desc.InputLayoutName = "Quad";
	Desc.BSName = "Default";
	Desc.RSName = "Default";
	Desc.DSSName = "Default";
	UEngineMaterial::Create("Tilemap", Desc);
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
		std::shared_ptr<UEngineShader> VertexShader = UEngineShaderFactory::Create(File, EShaderType::VS);
		std::shared_ptr<UEngineShader> PixelShader = UEngineShaderFactory::Create(File, EShaderType::PS);
	}

}
