#pragma once
#include "EngineState.h"

// 클래스 설명 :
class UEngineBlendState : public UEngineState
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

	virtual void Bind()override;

	ENGINE_API static std::shared_ptr<UEngineBlendState> Create(std::string_view _Name);
	ENGINE_API static std::shared_ptr<UEngineBlendState> Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc);
protected:

private:
	void CreateBlendState(D3D11_BLEND_DESC _Desc);
	ComPtr<ID3D11BlendState> BlendState = nullptr;
};
