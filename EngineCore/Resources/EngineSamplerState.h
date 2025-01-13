#pragma once
#include <EngineCore/Resources/EngineShader.h>

// 클래스 설명 :
class UEngineSamplerState : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineSamplerState();
	~UEngineSamplerState();

	// Delete Function
	UEngineSamplerState(const UEngineSamplerState& _Other) = delete;
	UEngineSamplerState(UEngineSamplerState&& _Other) noexcept = delete;
	UEngineSamplerState& operator=(const UEngineSamplerState& _Other) = delete;
	UEngineSamplerState& operator=(UEngineSamplerState&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineSamplerState> Create(std::string_view _Name);
	static std::shared_ptr<UEngineSamplerState> Create(std::string_view _Name, D3D11_SAMPLER_DESC _Desc);
	void CreateSamplerState(D3D11_SAMPLER_DESC _Desc);
	void Bind(EShaderType _Type, Uint32 Slot = 0) const;
protected:

private:
	ComPtr<ID3D11SamplerState> SamplerState;
};
