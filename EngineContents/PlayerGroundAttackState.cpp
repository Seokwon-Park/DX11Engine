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

	if (ComboCount > 3 || UEngineCore::GetEngineCurrentTime() >= lastTimeAttacked + 1.0f)
	{
		ComboCount = 0;
	}

	Player->GetAnimatorComponent()->SetAnimation(AnimationName+std::to_string(ComboCount));
	Rigidbody2D->SetZeroGravity();
}

void PlayerGroundAttackState::Update()
{
	PlayerState::Update();

	//if (!player.IsGroundDetected())
	//{
	//    stateMachine.ChangeState(player.airState);
	//}
	
	if (TriggerCalled == true)
	{
		StateMachine->ChangeState(Player->IdleState);
	}
}

void PlayerGroundAttackState::Exit()
{
	PlayerState::Exit();
	ComboCount++;
	lastTimeAttacked = UEngineCore::GetEngineCurrentTime();
}
