#pragma once
#include "EngineShader.h"

// Ό³Έν :
class UEngineVertexShader : public UEngineShader
{
public:
	UEngineVertexShader();
	virtual ~UEngineVertexShader();

	// delete Function
	UEngineVertexShader(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader(UEngineVertexShader&& _Other) noexcept = delete;
	UEngineVertexShader& operator=(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader& operator=(UEngineVertexShader&& _Other) noexcept = delete;

	virtual void Bind() const;
	virtual void CompilePath() override;
protected:

private:
	ComPtr<ID3D11VertexShader> VertexShader;
};

