#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
{
	Test = CreateDefaultSubObject<USpriteRendererComponent>();
	Input = CreateDefaultSubObject<UInputComponent>();
	Input->BindAction(EKey::Left, KeyEvent::Down, std::bind(&APlayer::TestFn, this));

	Test->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

}
void APlayer::TestFn()
{
	std::cout << "Test\n";
	AddActorLocation(FVector4::LEFT);
}
void APlayer::BeginPlay()
{
	APawn::BeginPlay();
}
