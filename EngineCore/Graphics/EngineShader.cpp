#include "EnginePCH.h"
#include "EngineShader.h"
#include "EngineCore.h"
#include "Graphics/DirectX11/DX11Shader.h"

EngineShader::EngineShader()
{
}

EngineShader::~EngineShader()
{
}

std::shared_ptr<EngineShader> EngineShader::Create(const std::string& _FilePath)
{
	switch (UEngineCore::GraphicsDevice->GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11Shader>(_FilePath);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

std::shared_ptr<EngineShader> EngineShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	return std::shared_ptr<EngineShader>();
}
