#pragma once
#include "EngineShader.h"

// ���� :
class UEngineVertexShader : public UEngineShader
{
public:
	UEngineVertexShader(std::string_view _FilePath, EShaderType _ShaderType);
	virtual ~UEngineVertexShader();

	// delete Function
	UEngineVertexShader(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader(UEngineVertexShader&& _Other) noexcept = delete;
	UEngineVertexShader& operator=(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader& operator=(UEngineVertexShader&& _Other) noexcept = delete;

	virtual void Bind() const;

	ID3DBlob* GetShaderBlob() const { return ShaderBlob.Get(); }
protected:

private:
	ComPtr<ID3D11VertexShader> VertexShader;
};
