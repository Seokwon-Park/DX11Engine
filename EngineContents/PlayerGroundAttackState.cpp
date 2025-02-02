#include "EnginePCH.h"
#include "PlayerGroundAttackState.h"
#include "Player.h"

PlayerGroundAttackState::PlayerGroundAttackState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerGroundState(_Player, _StateMachine, _AnimationName)
{
}

PlayerGroundAttackState::~PlayerGroundAttackState()
{
}

void PlayerGroundAttackState::Enter()
{
	PlayerState::Enter();
	Rigidbody2D->SetZeroGravity();
}

void PlayerGroundAttackState::Update()
{
	PlayerState::Update();

	if (UEngineInputSystem::GetKeyDown(EKey::X))
	{
		//Attack
		// stateMachine.ChangeState(player.primaryAttackState);
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

void PlayerGroundAttackState::Exit()
{
	PlayerState::Exit();
}
