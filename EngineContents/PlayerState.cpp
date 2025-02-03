#include "EnginePCH.h"
#include "PlayerState.h"
#include "BaseStateMachine.h"
#include "Player.h"

PlayerState::PlayerState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:BaseState()
{
	Player = _Player;
	StateMachine = _StateMachine;
	AnimationName = _AnimationName;
}

PlayerState::~PlayerState()
{
}

void PlayerState::Enter()
{
	Player->GetAnimatorComponent()->SetAnimation(AnimationName);
	Rigidbody2D = Player->GetRigidbody2DComponent();
	TriggerCalled = false;
}

void PlayerState::Update()
{
	if (UEngineInputSystem::GetKey(EKey::Left))
	{
		XInput = -1.0f;
	}
	if (UEngineInputSystem::GetKey(EKey::Right))
	{
		XInput = 1.0f;
	}
	if (UEngineInputSystem::GetKeyFree(EKey::Left) && UEngineInputSystem::GetKeyFree(EKey::Right))
	{
		XInput = 0.0f;
	}
}


void PlayerState::Exit()
{
}
