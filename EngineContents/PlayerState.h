#pragma once
#include "BaseState.h"

// Ό³Έν :
class PlayerState : public BaseState
{
public:
	// constrcuter destructer
	PlayerState(class APlayer* _Player, class BaseStateMachine* _StateMachine, std::string_view _AnimationName);
	~PlayerState();

	// delete Function
	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(PlayerState&& _Other) noexcept = delete;

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

	void AnimationEndTrigger() { TriggerCalled = true; }

protected:
	bool TriggerCalled = false;
	class APlayer* Player;
	std::string AnimationName;
	class URigidbody2DComponent* Rigidbody2D;

	float XInput = 0.0f;
	float YInput = 0.0f;
	
private:

};

