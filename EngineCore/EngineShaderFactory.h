#pragma once
#include "Resources/EngineVertexShader.h"
#include "Resources/EnginePixelShader.h"

// 클래스 설명 :
class UEngineShaderFactory
{
public:
	// Constrcuter Destructer
	UEngineShaderFactory();
	~UEngineShaderFactory();

	// Delete Function
	UEngineShaderFactory(const UEngineShaderFactory& _Other) = delete;
	UEngineShaderFactory(UEngineShaderFactory&& _Other) noexcept = delete;
	UEngineShaderFactory& operator=(const UEngineShaderFactory& _Other) = delete;
	UEngineShaderFactory& operator=(UEngineShaderFactory&& _Other) noexcept = delete;

	ENGINE_API static std::shared_ptr<class UEngineShader> Create(std::string_view _FilePath, EShaderType _ShaderType);
protected:

private:

};
