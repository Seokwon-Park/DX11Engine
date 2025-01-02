#include "EnginePCH.h"
#include "StateMachine.h"
#include "BaseState.h"


StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}


void StateMachine::InitState(BaseState* _NextState)
{
	CurrentState = _NextState;
	CurrentState->Enter();
}

void StateMachine::ChangeState(BaseState* _NextState)
{
	CurrentState->Exit();
	CurrentState = _NextState;
	CurrentState->Enter();
}
