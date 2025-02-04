#include "EnginePCH.h"
#include "PlayerGroundAttackState.h"
#include "Player.h"
#include"AttackEffect.h"

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

	if (ComboCount > 3 || UEngineCore::GetEngineCurrentTime() >= lastTimeAttacked + 0.5f)
	{
		ComboCount = 0;
	}

	Player->GetAnimatorComponent()->SetAnimation(AnimationName+std::to_string(ComboCount));
	Rigidbody2D->SetZeroGravity();
	auto AttackEffect = Player->GetLevel()->SpawnActor<AAttackEffect>("AttackEffect");
	AttackEffect->SetActorLocation(Player->GetActorLocation());
	
	if (Player->FacingDir == 1)
	{
		AttackEffect->SetActorRotation({ 0.0f, 180.0f,0.0f, 0.0f });
	}
	else
	{
		AttackEffect->SetActorRotation({ 0.0f, 0.0f,0.0f, 0.0f });
	}
	AttackEffect->SetupEffect("TeviGroundAttackEffect" + std::to_string(ComboCount));

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
		if (UEngineInputSystem::GetKey(EKey::X))
		{
			StateMachine->ChangeState(Player->AttackState);
		}
		else
		{
			StateMachine->ChangeState(Player->IdleState);
		}
	}
}

void PlayerGroundAttackState::Exit()
{
	PlayerState::Exit();
	ComboCount++;
	lastTimeAttacked = UEngineCore::GetEngineCurrentTime();
}
