#pragma once
#include "PlayerState.h"

// ���� :
class PlayerAirState : public PlayerState
{
public:
	// constrcuter destructer
	PlayerAirState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerAirState();

	// delete Function
	PlayerAirState(const PlayerAirState& _Other) = delete;
	PlayerAirState(PlayerAirState&& _Other) noexcept = delete;
	PlayerAirState& operator=(const PlayerAirState& _Other) = delete;
	PlayerAirState& operator=(PlayerAirState&& _Other) noexcept = delete;

protected:
	void Enter() override;
	void Update() override;
	void Exit() override;
private:

};

