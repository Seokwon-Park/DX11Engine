#pragma once

// 클래스 설명 :
class UEngineDepthStencilState 
{
public:
	// Constrcuter Destructer
	UEngineDepthStencilState();
	~UEngineDepthStencilState();

	// Delete Function
	UEngineDepthStencilState(const UEngineDepthStencilState& _Other) = delete;
	UEngineDepthStencilState(UEngineDepthStencilState&& _Other) noexcept = delete;
	UEngineDepthStencilState& operator=(const UEngineDepthStencilState& _Other) = delete;
	UEngineDepthStencilState& operator=(UEngineDepthStencilState&& _Other) noexcept = delete;
protected:

private:
	ComPtr<ID3D11DepthStencilState> DepthStencilState = nullptr;
};
