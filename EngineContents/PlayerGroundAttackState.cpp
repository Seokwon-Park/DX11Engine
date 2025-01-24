#include "EnginePCH.h"
#include "PlayerGroundAttackState.h"

PlayerGroundAttackState::PlayerGroundAttackState(APlayer* _Player, BaseStateMachine* _StateMachine, std::string_view _AnimationName)
	:PlayerGroundState(_Player, _StateMachine, _AnimationName)
{
}

PlayerGroundAttackState::~PlayerGroundAttackState()
{
}
