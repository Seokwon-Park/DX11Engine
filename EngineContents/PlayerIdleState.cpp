#include "EnginePCH.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerIdleState::PlayerIdleState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerGroundState(_Player, _StateMachine, _AnimationName)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Enter()
{
	PlayerGroundState::Enter();

	Player->SetVelocity({0.0f, 0.0f});
	Rigidbody2D->SetZeroGravity();
}

void PlayerIdleState::Update()
{
	PlayerGroundState::Update();

	if (XInput != 0.0f)
		StateMachine->ChangeState(Player->RunState);
}

void PlayerIdleState::Exit()
{
	PlayerGroundState::Exit();
	Rigidbody2D->SetGravity(1.0f);
}
