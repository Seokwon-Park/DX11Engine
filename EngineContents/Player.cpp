#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{
	Test = CreateDefaultSubObject<USpriteRendererComponent>();
	Test->SetRelativeScale3D({ 50.0f,50.0f,1.0f });

	Input = CreateDefaultSubObject<UInputComponent>();
	Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::LEFT));
	Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::RIGHT));
	Input->BindAction(EKey::Up, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::UP));
	Input->BindAction(EKey::Down, KeyEvent::Press, std::bind(&APlayer::Move, this, FVector4::DOWN));

	Test->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	//EngineLogger::Test<int>();

}
void APlayer::Move(FVector4 _Dir)
{
	//AddActorLocation(_Dir * UEngineCore::GetDeltaTime());
	AddActorLocation(_Dir);
}
void APlayer::BeginPlay()
{
	APawn::BeginPlay();
}
