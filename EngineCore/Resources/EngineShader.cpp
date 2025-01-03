#include "EnginePCH.h"
#include "EngineShader.h"
#include <EngineCore/DirectX11/DX11Shader.h>

UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
}

ENGINE_API std::vector<std::shared_ptr<UEngineShader>> UEngineShader::CreateShaders(std::string_view _FilePath, std::vector<EShaderType> _ShaderTypes)
{
	std::vector<std::shared_ptr<UEngineShader>> Result;
	for (EShaderType ShaderType : _ShaderTypes)
	{
		Result.push_back(Create(_FilePath, ShaderType));
	}
	return Result;
}

ENGINE_API std::shared_ptr<UEngineShader> UEngineShader::Create(std::string_view _FilePath, EShaderType _ShaderType)
{
	switch (_ShaderType)
	{
	case EShaderType::VS:
		return std::make_shared<UEngineVertexShader>(_FilePath, _ShaderType);
		break;
	case EShaderType::HS:
		break;
	case EShaderType::DS:
		break;
	case EShaderType::GS:
		break;
	case EShaderType::PS:
		return std::make_shared<DX11PixelShader>(_FilePath, _ShaderType);
		break;
	case EShaderType::CS:
		break;
	default:
		return nullptr;
	}
	return nullptr;
}

//std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _FilePath)
//{
//	switch (UEngineCore::GetRendererAPI())
//	{
//	case ERendererAPI::DirectX11:
//		return std::make_shared<DX11Shader>(_FilePath);
//	case ERendererAPI::None:
//		return nullptr;
//	default:
//		return nullptr;
//	}
//}
//
//std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _Name, const std::string& vertexSrc, const std::string& fragmentSrc)
//{
//	return std::shared_ptr<UEngineShader>();
//}


