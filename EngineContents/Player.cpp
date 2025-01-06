#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();
	SpriteRenderer->SetRelativeScale3D({ 50.0f,50.0f,1.0f });
	SpriteRenderer->SetOrder(ESortingLayer::Default, -1);

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);
	//Animator->SetAnimation("TeviIdle");
	Animator->SetAnimation("TeviRun");

	Input = CreateDefaultSubobject<UInputComponent>();
	Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::LEFT));
	Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::RIGHT));
	Input->BindAction(EKey::Up, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::UP));
	Input->BindAction(EKey::Down, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::DOWN));

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

	int a = 0;
}

void APlayer::Move(FVector4 _Dir)
{
	//AddActorLocation(_Dir * UEngineCore::GetDeltaTime());
	AddActorLocation(_Dir * 0.1f);
	//AddActorRotation(FVector4(0.0f, 0.0f, 0.01f, 0.0f));
}
