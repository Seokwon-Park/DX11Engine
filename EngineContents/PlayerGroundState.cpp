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
}

void PlayerGroundState::Update()
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
	}
}

void PlayerGroundState::Exit()
{
	PlayerState::Exit();
}
