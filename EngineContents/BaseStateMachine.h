#pragma once

// Ό³Έν :
class BaseStateMachine
{
public:
	// constrcuter destructer
	BaseStateMachine();
	~BaseStateMachine();

	// delete Function
	BaseStateMachine(const BaseStateMachine& _Other) = delete;
	BaseStateMachine(BaseStateMachine&& _Other) noexcept = delete;
	BaseStateMachine& operator=(const BaseStateMachine& _Other) = delete;
	BaseStateMachine& operator=(BaseStateMachine&& _Other) noexcept = delete;

	virtual void InitState(class BaseState* _NextState);
	virtual void ChangeState(class BaseState* _NextState);

	class BaseState* CurrentState = nullptr;
protected:

private:
};

