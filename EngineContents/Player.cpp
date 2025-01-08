#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{
	RigidBody2D = CreateDefaultSubobject<URigidbody2DComponent>();
	BoxCollider2D = CreateDefaultSubobject<UBoxCollider2DComponent>();
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);
	//Animator->SetAnimation("TeviIdle");
	Animator->SetAnimation("TeviWalk");

	BoxCollider2D->SetRigidbody(RigidBody2D);
	BoxCollider2D->SetCollisionLayer(ECollisionLayer::Player);
	//Input = CreateDefaultSubobject<UInputComponent>();
	//Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::LEFT));
	//Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::RIGHT));
	//Input->BindAction(EKey::Up, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::UP));
	//Input->BindAction(EKey::Down, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::DOWN));
	
	RigidBody2D->SetupAttachment(RootComponent);
	BoxCollider2D->SetupAttachment(RootComponent);
	SpriteRenderer->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	//EngineLogger::Test<int>();
	RigidBody2D->SetVelocity({ 0.0f, 0.0f });
	if (UEngineInputSystem::GetKey(EKey::Left))
	{
		RigidBody2D->SetVelocity(FVector2::LEFT*100.0f);
	}
	if (UEngineInputSystem::GetKey(EKey::Right))
	{
		RigidBody2D->SetVelocity(FVector2::RIGHT * 100.0f);
	}
}

void APlayer::BeginPlay()
{
	APawn::BeginPlay();
}

void APlayer::Move(FVector4 _Dir)
{
	//AddActorLocation(_Dir * UEngineCore::GetDeltaTime());
	RigidBody2D->SetVelocity({100.0f, 0.0f});
	//AddActorLocation(_Dir*UEngineCore::GetEngineDeltaTime());
}
