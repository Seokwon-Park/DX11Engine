#pragma once
#include <EngineCore/Components/InputComponent.h>


#include "Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"

// Ό³Έν :
class APlayer : public AEntity
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	void SetVelocity(FVector2 _Velocity);

	std::shared_ptr<PlayerStateMachine> StateMachine;
	std::shared_ptr<PlayerIdleState> IdleState;
	std::shared_ptr<PlayerRunState> RunState;
	std::shared_ptr<PlayerJumpState> JumpState;

	float JumpForce = 4.0f;

protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UInputComponent> Input;


	
};

