#include"EnginePCH.h"
#include "EngineShaderFactory.h"
#include "ResourceManager.h"



UEngineShaderFactory::UEngineShaderFactory()
{
}

UEngineShaderFactory::~UEngineShaderFactory()
{
}

ENGINE_API std::shared_ptr<UEngineShader> UEngineShaderFactory::Create(UEngineFile _File, EShaderType _ShaderType)
{
	std::shared_ptr<UEngineShader> NewShader;
	std::string Prefix = "";
	switch (_ShaderType)
	{
	case EShaderType::VS:
		NewShader = std::make_shared<UEngineVertexShader>();
		Prefix = "VS";
		break;
	case EShaderType::HS:
		Prefix = "HS";
		break;
	case EShaderType::DS:
		Prefix = "DS";
		break;
	case EShaderType::GS:
		Prefix = "GS";
		break;
	case EShaderType::PS:
		NewShader = std::make_shared<UEnginePixelShader>();
		Prefix = "PS";
		break;
	case EShaderType::CS:
		break;
	default:
		return nullptr;
	}
	NewShader->Init(_File.ToString(), _ShaderType);
	NewShader->CompilePath();
	UResourceManager::AddResource<UEngineShader>(NewShader,_File.GetFileNameWithoutExtension()+Prefix, _File.ToString());
	return NewShader;
}

