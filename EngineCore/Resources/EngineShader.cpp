#include "EnginePCH.h"
#include "EngineShader.h"
#include "EngineCore.h"
#include "DirectX11/DX11Shader.h"

UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
}

std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _FilePath)
{
	switch (UEngineCore::GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11Shader>(_FilePath);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _Name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	return std::shared_ptr<UEngineShader>();
}
