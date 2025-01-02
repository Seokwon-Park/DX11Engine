#pragma once

// Ό³Έν :
class StateMachine
{
public:
	// constrcuter destructer
	StateMachine();
	~StateMachine();

	// delete Function
	StateMachine(const StateMachine& _Other) = delete;
	StateMachine(StateMachine&& _Other) noexcept = delete;
	StateMachine& operator=(const StateMachine& _Other) = delete;
	StateMachine& operator=(StateMachine&& _Other) noexcept = delete;

	virtual void InitState(class BaseState* _NextState);
	virtual void ChangeState(class BaseState* _NextState);

protected:

private:
	class BaseState* CurrentState = nullptr;
};

