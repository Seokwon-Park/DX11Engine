#pragma once
#include "PlayerGroundState.h"

// ���� :
class PlayerIdleState : public PlayerGroundState
{
public:
	// constrcuter destructer
	PlayerIdleState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerIdleState();

	// delete Function
	PlayerIdleState(const PlayerIdleState& _Other) = delete;
	PlayerIdleState(PlayerIdleState&& _Other) noexcept = delete;
	PlayerIdleState& operator=(const PlayerIdleState& _Other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& _Other) noexcept = delete;
protected:

private:
	// PlayerState��(��) ���� ��ӵ�
	void Enter() override;
	void Update() override;
	void Exit() override;

};

