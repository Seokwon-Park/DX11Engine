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


}

void PlayerAirState::Exit()
{
	PlayerState::Exit();
}
