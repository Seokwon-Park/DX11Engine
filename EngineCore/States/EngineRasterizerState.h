#pragma once

// Ό³Έν :
class UEngineRasterizerState 
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

	void Bind();

	ENGINE_API static std::shared_ptr<UEngineRasterizerState> Create(std::string_view _Name);
	ENGINE_API static std::shared_ptr<UEngineRasterizerState> Create(std::string_view _Name, D3D11_RASTERIZER_DESC _Desc);
protected:

private:
	void CreateRasterizerState(D3D11_RASTERIZER_DESC _Desc);
	ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;

};

