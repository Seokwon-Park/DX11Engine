#include"EnginePCH.h"
#include "EngineShaderFactory.h"



UEngineShaderFactory::UEngineShaderFactory()
{
}

UEngineShaderFactory::~UEngineShaderFactory()
{
}

ENGINE_API std::shared_ptr<UEngineShader> UEngineShaderFactory::Create(std::string_view _FilePath, EShaderType _ShaderType)
{
	std::shared_ptr<UEngineShader> NewShader;
	switch (_ShaderType)
	{
	case EShaderType::VS:
		NewShader = std::make_shared<UEngineVertexShader>();
		break;
	case EShaderType::HS:
		break;
	case EShaderType::DS:
		break;
	case EShaderType::GS:
		break;
	case EShaderType::PS:
		NewShader = std::make_shared<UEnginePixelShader>();
		break;
	case EShaderType::CS:
		break;
	default:
		return nullptr;
	}
	NewShader->Init(_FilePath, _ShaderType);
	NewShader->Compile();
	return NewShader;
}

