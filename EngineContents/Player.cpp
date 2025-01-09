#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{

}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	StateMachine->CurrentState->Update();

}

void APlayer::BeginPlay()
{
	APawn::BeginPlay();

	StateMachine = std::make_shared<PlayerStateMachine>();
	IdleState = std::make_shared<PlayerIdleState>(this, StateMachine.get(), "TeviIdle");
	RunState = std::make_shared<PlayerRunState>(this, StateMachine.get(), "TeviRun");

	StateMachine->InitState(IdleState.get());
}

void APlayer::SetVelocity(FVector2 _Velocity)
{
	RigidBody2D->SetVelocity(_Velocity);
}
