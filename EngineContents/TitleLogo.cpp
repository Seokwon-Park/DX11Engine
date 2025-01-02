#include "EnginePCH.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();
	SpriteRenderer->SetSprite("Tevi", 99);
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}
