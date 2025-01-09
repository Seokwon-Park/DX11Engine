#pragma once
#include "PlayerState.h"

// 클래스 설명 :
class PlayerJumpState : public PlayerState
{
public:
	// Constrcuter Destructer
	PlayerJumpState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerJumpState();

	// Delete Function
	PlayerJumpState(const PlayerJumpState& _Other) = delete;
	PlayerJumpState(PlayerJumpState&& _Other) noexcept = delete;
	PlayerJumpState& operator=(const PlayerJumpState& _Other) = delete;
	PlayerJumpState& operator=(PlayerJumpState&& _Other) noexcept = delete;

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
protected:


private:

};
