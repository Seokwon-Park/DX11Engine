#include "EnginePCH.h"
#include "Entity.h"

AEntity::AEntity()
{
	RigidBody2D = CreateDefaultSubobject<URigidbody2DComponent>();
	BoxCollider2D = CreateDefaultSubobject<UBoxCollider2DComponent>();
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);
	//Animator->SetAnimation("TeviIdle");

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

AEntity::~AEntity()
{
}

void AEntity::BeginPlay()
{
	APawn::BeginPlay();
}

void AEntity::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);
}
