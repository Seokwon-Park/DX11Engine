#pragma once
#include "PlayerGroundState.h"

// Ό³Έν :
class PlayerGroundAttackState : public PlayerGroundState
{
public:
	// constrcuter destructer
	PlayerGroundAttackState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName);
		
	~PlayerGroundAttackState();

	// delete Function
	PlayerGroundAttackState(const PlayerGroundAttackState& _Other) = delete;
	PlayerGroundAttackState(PlayerGroundAttackState&& _Other) noexcept = delete;
	PlayerGroundAttackState& operator=(const PlayerGroundAttackState& _Other) = delete;
	PlayerGroundAttackState& operator=(PlayerGroundAttackState&& _Other) noexcept = delete;

protected:
	void Enter() override;
	void Update() override;
	void Exit() override;
private:

};

