#pragma once

// 클래스 설명 :
class UEngineSamplerState 
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

	static std::shared_ptr<UEngineSamplerState> Create();
	void Init();
	void Bind() const;
protected:

private:
	ComPtr<ID3D11SamplerState> SamplerState;
};
