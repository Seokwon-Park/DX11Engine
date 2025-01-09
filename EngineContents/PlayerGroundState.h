#pragma once
#include "PlayerState.h"

// 클래스 설명 :
class PlayerGroundState :public PlayerState
{
public:
	// Constrcuter Destructer
	PlayerGroundState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerGroundState();

	// Delete Function
	PlayerGroundState(const PlayerGroundState& _Other) = delete;
	PlayerGroundState(PlayerGroundState&& _Other) noexcept = delete;
	PlayerGroundState& operator=(const PlayerGroundState& _Other) = delete;
	PlayerGroundState& operator=(PlayerGroundState&& _Other) noexcept = delete;
protected:
	void Enter() override;
	void Update() override;
	void Exit() override;
private:

};
