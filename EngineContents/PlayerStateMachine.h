#pragma once
#include "BaseStateMachine.h"
#include "PlayerState.h"

// Ό³Έν :
class PlayerStateMachine : public BaseStateMachine
{
public:
	// constrcuter destructer
	PlayerStateMachine();
	~PlayerStateMachine();

	// delete Function
	PlayerStateMachine(const PlayerStateMachine& _Other) = delete;
	PlayerStateMachine(PlayerStateMachine&& _Other) noexcept = delete;
	PlayerStateMachine& operator=(const PlayerStateMachine& _Other) = delete;
	PlayerStateMachine& operator=(PlayerStateMachine&& _Other) noexcept = delete;

protected:

private:
};

