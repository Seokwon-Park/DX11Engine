#pragma once

// Ό³Έν :
class EngineRasterizerState
{
public:
	// constrcuter destructer
	EngineRasterizerState();
	~EngineRasterizerState();

	// delete Function
	EngineRasterizerState(const EngineRasterizerState& _Other) = delete;
	EngineRasterizerState(EngineRasterizerState&& _Other) noexcept = delete;
	EngineRasterizerState& operator=(const EngineRasterizerState& _Other) = delete;
	EngineRasterizerState& operator=(EngineRasterizerState&& _Other) noexcept = delete;

protected:

private:

};

