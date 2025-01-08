#pragma once
#include "EngineState.h"

// Ŭ���� ���� :
class UEngineDepthStencilState : public UEngineState
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
	virtual void Bind()override;

	ENGINE_API static std::shared_ptr<UEngineDepthStencilState> Create(std::string_view _Name);
	ENGINE_API static std::shared_ptr<UEngineDepthStencilState> Create(std::string_view _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc);
protected:

private:
	void CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC _Desc);
	ComPtr<ID3D11DepthStencilState> DepthStencilState = nullptr;
};
