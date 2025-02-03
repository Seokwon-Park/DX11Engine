#include "EnginePCH.h"
#include "PlayerGroundState.h"
#include "Player.h"


PlayerGroundState::PlayerGroundState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerState(_Player, _StateMachine, _AnimationName)
{
}

PlayerGroundState::~PlayerGroundState()
{
}

void PlayerGroundState::Enter()
{
	PlayerState::Enter();
	Rigidbody2D->SetZeroGravity();
}

void PlayerGroundState::Update()
{
	PlayerState::Update();

	if (UEngineInputSystem::GetKeyDown(EKey::X))
	{
		//Attack
		 StateMachine->ChangeState(Player->AttackState);
	}

	//if (!player.IsGroundDetected())
	//{
	//    stateMachine.ChangeState(player.airState);
	//}

	if (UEngineInputSystem::GetKeyDown(EKey::C) /* && player.IsGroundDetected()*/)
	{
		StateMachine->ChangeState(Player->JumpState);
		Rigidbody2D->SetGravity(1.0f);
	}

	if (false == Player->IsGroundDetected())
	{
		StateMachine->ChangeState(Player->AirState);
		Rigidbody2D->SetGravity(1.0f);
	}
}

void PlayerGroundState::Exit()
{
	PlayerState::Exit();
}
