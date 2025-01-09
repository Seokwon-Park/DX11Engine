#pragma once
#include "BaseStateMachine.h"

class BaseState
{
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
protected:
	class BaseStateMachine* StateMachine;
private:

};