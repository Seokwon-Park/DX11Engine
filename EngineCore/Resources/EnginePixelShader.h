#pragma once

// ���� :
class UEnginePixelShader
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

protected:

private:

};

