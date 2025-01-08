#pragma once
#include <EngineCore/StateManager.h>

// Ό³Έν :
class UEngineState : public UObject
{
public:
	// constrcuter destructer
	UEngineState();
	~UEngineState();

	// delete Function
	UEngineState(const UEngineState& _Other) = delete;
	UEngineState(UEngineState&& _Other) noexcept = delete;
	UEngineState& operator=(const UEngineState& _Other) = delete;
	UEngineState& operator=(UEngineState&& _Other) noexcept = delete;

	virtual void Bind() = 0;
protected:

private:

};

