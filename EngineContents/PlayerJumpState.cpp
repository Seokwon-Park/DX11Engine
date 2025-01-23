#include "EnginePCH.h"
#include "PlayerJumpState.h"
#include "Player.h"

PlayerJumpState::PlayerJumpState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerState(_Player, _StateMachine, _AnimationName)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Enter()
{
	PlayerState::Enter();

	Player->SetVelocity({ Rigidbody2D->GetVelocity().X, Player->JumpForce });
}

void PlayerJumpState::Update()
{
	PlayerState::Update();

	//Player->SetVelocity({ 100.0f * XInput , Rigidbody2D->GetVelocity().Y });

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

	if (Rigidbody2D->GetVelocity().Y <= 0.0f)
	{
		StateMachine->ChangeState(Player->AirState);
	}
}

void PlayerJumpState::Exit()
{
	PlayerState::Exit();
}
