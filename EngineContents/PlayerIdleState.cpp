#include "EnginePCH.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerIdleState::PlayerIdleState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerState(_Player, _StateMachine, _AnimationName)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Enter()
{
	PlayerState::Enter();

	Player->SetVelocity({0.0f, 0.0f});
}

void PlayerIdleState::Update()
{
	PlayerState::Update();

	if (XInput != 0.0f)
		StateMachine->ChangeState(Player->RunState.get());
}

void PlayerIdleState::Exit()
{
	PlayerState::Exit();
}
