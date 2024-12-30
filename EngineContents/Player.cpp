#include "EnginePCH.h"
#include "Player.h"

APlayer::APlayer()
{
	Test = CreateDefaultSubObject<USpriteRendererComponent>();
	Input = CreateDefaultSubObject<UInputComponent>();
	Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&APlayer::TestFn, this));
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
}
void APlayer::BeginPlay()
{
	APawn::BeginPlay();
}
