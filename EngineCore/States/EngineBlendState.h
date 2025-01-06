#pragma once

// 클래스 설명 :
class UEngineBlendState 
{
public:
	// Constrcuter Destructer
	UEngineBlendState();
	~UEngineBlendState();

	// Delete Function
	UEngineBlendState(const UEngineBlendState& _Other) = delete;
	UEngineBlendState(UEngineBlendState&& _Other) noexcept = delete;
	UEngineBlendState& operator=(const UEngineBlendState& _Other) = delete;
	UEngineBlendState& operator=(UEngineBlendState&& _Other) noexcept = delete;
protected:

private:
	ComPtr<ID3D11BlendState> BlendState = nullptr;
};
