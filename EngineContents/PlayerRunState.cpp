#include "EnginePCH.h"
#include "PlayerRunState.h"
#include "Player.h"

PlayerRunState::PlayerRunState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerGroundState(_Player, _StateMachine, _AnimationName)
{
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::Enter()
{
	PlayerGroundState::Enter();
}

void PlayerRunState::Update()
{
	PlayerGroundState::Update();

	Player->SetVelocity({ 100.0f * XInput , Rigidbody2D->GetVelocity().Y });
//	//EngineLogger::Test<int>();
////RigidBody2D->SetVelocity({ 0.0f, 0.0f });
//	if (UEngineInputSystem::GetKey(EKey::Left))
//	{
//		Rigidbody2D->SetVelocity(FVector2::LEFT * 100.0f);
//	}
//	if (UEngineInputSystem::GetKey(EKey::Right))
//	{
//		Rigidbody2D->SetVelocity(FVector2::RIGHT * 100.0f);
//	}
//	if (UEngineInputSystem::GetKeyDown(EKey::Space))
//	{
//		Rigidbody2D->SetVelocity(FVector2::UP * 2000.0f);
//	}
	if (XInput == 0.0f)
	{
		StateMachine->ChangeState(Player->IdleState);
	}
}

void PlayerRunState::Exit()
{
	PlayerGroundState::Exit();
}
