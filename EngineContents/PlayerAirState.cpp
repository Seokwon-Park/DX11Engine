#include "EnginePCH.h"
#include "PlayerAirState.h"
#include "Player.h"


PlayerAirState::PlayerAirState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerState(_Player, _StateMachine, _AnimationName)
{
}

PlayerAirState::~PlayerAirState()
{
}

void PlayerAirState::Enter()
{
	PlayerState::Enter();
}

void PlayerAirState::Update()
{
	PlayerState::Update();

	Player->SetVelocity({ XInput * Player->MoveSpeed, Rigidbody2D->GetVelocity().Y });

	if (Player->IsGroundDetected())
	{
		StateMachine->ChangeState(Player->IdleState);
	}

}

void PlayerAirState::Exit()
{
	PlayerState::Exit();
}
