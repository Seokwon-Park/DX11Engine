#pragma once
#include "EngineShader.h"

// Ό³Έν :
class UEnginePixelShader : public UEngineShader
{
public:
	// constrcuter destructer
	UEnginePixelShader();
	~UEnginePixelShader();

	// delete Function
	UEnginePixelShader(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader(UEnginePixelShader&& _Other) noexcept = delete;
	UEnginePixelShader& operator=(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader& operator=(UEnginePixelShader&& _Other) noexcept = delete;

	virtual void Bind() const override;
	virtual void Compile() override;
protected:

private:
	ComPtr<ID3D11PixelShader> PixelShader;
};

