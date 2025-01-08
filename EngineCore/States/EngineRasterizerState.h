#pragma once
#include "EngineState.h"

// Ό³Έν :
class UEngineRasterizerState : public UEngineState
{
public:
	// constrcuter destructer
	UEngineRasterizerState();
	~UEngineRasterizerState();

	// delete Function
	UEngineRasterizerState(const UEngineRasterizerState& _Other) = delete;
	UEngineRasterizerState(UEngineRasterizerState&& _Other) noexcept = delete;
	UEngineRasterizerState& operator=(const UEngineRasterizerState& _Other) = delete;
	UEngineRasterizerState& operator=(UEngineRasterizerState&& _Other) noexcept = delete;

	virtual void Bind() override;

	ENGINE_API static std::shared_ptr<UEngineRasterizerState> Create(std::string_view _Name);
	ENGINE_API static std::shared_ptr<UEngineRasterizerState> Create(std::string_view _Name, const D3D11_RASTERIZER_DESC& _Desc);
protected:

private:
	void CreateRasterizerState(D3D11_RASTERIZER_DESC _Desc);
	ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;

};

