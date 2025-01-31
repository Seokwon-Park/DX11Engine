#pragma once
#include <EngineCore/Components/InputComponent.h>


#include "Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerAirState.h"

// ���� :
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


	std::shared_ptr<PlayerStateMachine> StateMachine;
	std::shared_ptr<PlayerIdleState> IdleState;
	std::shared_ptr<PlayerRunState> RunState;
	std::shared_ptr<PlayerJumpState> JumpState;
	std::shared_ptr<PlayerAirState> AirState;

	float JumpForce = 5.0f;
	float MoveSpeed = 3.0f;

protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UInputComponent> Input;


	
};

