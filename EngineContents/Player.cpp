#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{
	RigidBody = CreateDefaultSubobject<RigidBody2DComponent>();
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);
	//Animator->SetAnimation("TeviIdle");
	Animator->SetAnimation("TeviWalk");

	Input = CreateDefaultSubobject<UInputComponent>();
	Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::LEFT));
	Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::RIGHT));
	Input->BindAction(EKey::Up, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::UP));
	Input->BindAction(EKey::Down, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::DOWN));

	RigidBody->SetupAttachment(RootComponent);
	SpriteRenderer->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	//EngineLogger::Test<int>();

}

void APlayer::BeginPlay()
{
	APawn::BeginPlay();
}

void APlayer::Move(FVector4 _Dir)
{
	//AddActorLocation(_Dir * UEngineCore::GetDeltaTime());
	AddActorLocation(_Dir);
}
