#include "EnginePCH.h"
#include "BaseStateMachine.h"
#include "BaseState.h"


BaseStateMachine::BaseStateMachine()
{
}

BaseStateMachine::~BaseStateMachine()
{
}


void BaseStateMachine::InitState(std::shared_ptr<BaseState> _NextState)
{
	CurrentState = _NextState;
	CurrentState->Enter();
}

void BaseStateMachine::ChangeState(std::shared_ptr<BaseState> _NextState)
{
	CurrentState->Exit();
	CurrentState = _NextState;
	CurrentState->Enter();
}
