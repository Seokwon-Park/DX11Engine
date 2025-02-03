#include "EnginePCH.h"
#include "Entity.h"
#include <EngineCore/EnginePhysics.h>

AEntity::AEntity()
{
	RigidBody2D = CreateDefaultSubobject<URigidbody2DComponent>();
	//BoxCollider2D = CreateDefaultSubobject<UBoxCollider2DComponent>();
	CapsuleCollider2D = CreateDefaultSubobject<UCapsuleCollider2DComponent>();
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);
	//Animator->SetAnimation("TeviIdle");

	//BoxCollider2D->SetRigidbody(RigidBody2D);
	//BoxCollider2D->SetCollisionLayer(ECollisionLayer::Player);
	//Input = CreateDefaultSubobject<UInputComponent>();
	//Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::LEFT));
	//Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::RIGHT));
	//Input->BindAction(EKey::Up, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::UP));
	//Input->BindAction(EKey::Down, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::DOWN));

	CapsuleCollider2D->SetRigidbody(RigidBody2D);
	CapsuleCollider2D->SetCollisionLayer(ECollisionLayer::Player);

	RigidBody2D->SetupAttachment(RootComponent);
	CapsuleCollider2D->SetupAttachment(RootComponent);
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

void AEntity::Flip()
{
	FacingDir = FacingDir * -1;
	//FacingRight = !facingRight;
	AddActorRotation(FVector4(0, 180, 0));


	//if (onFlipped != null)
	//	onFlipped();
}

void AEntity::SetVelocity(FVector2 _Velocity)
{
	RigidBody2D->SetVelocity(_Velocity);

	if (RigidBody2D->GetVelocity().X > 0 && FacingDir == -1)
	{
		Flip();
	}
	else if (RigidBody2D->GetVelocity().X < 0 && FacingDir == 1)
	{
		Flip();
	}
}

bool AEntity::IsGroundDetected()
{
	return UEnginePhysics::RayCast(GetLevel(), GetActorLocation() + FVector4(11.0f, 0.0f, 0.0f), FVector4::DOWN, 29.0f, ECollisionLayer::Ground) || UEnginePhysics::RayCast(GetLevel(), GetActorLocation() + FVector4(-11.0f, 0.0f, 0.0f), FVector4::DOWN, 29.0f, ECollisionLayer::Ground);
}

