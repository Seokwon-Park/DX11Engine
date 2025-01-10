#pragma once
#include "PlayerGroundState.h"

// Ό³Έν :
class PlayerRunState : public PlayerGroundState
{
public:
	// constrcuter destructer
	PlayerRunState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerRunState();

	// delete Function
	PlayerRunState(const PlayerRunState& _Other) = delete;
	PlayerRunState(PlayerRunState&& _Other) noexcept = delete;
	PlayerRunState& operator=(const PlayerRunState& _Other) = delete;
	PlayerRunState& operator=(PlayerRunState&& _Other) noexcept = delete;

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
protected:

private:

};

