#include "EnginePCH.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();
	SpriteRenderer->SetSprite("Tevi", 99);
	SpriteRenderer->SetOrder(ESortingLayer::Default, -1);

	SpriteRenderer->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//SetActorLocation({ 100.0f, 0.0f, 1.0f, 1.0f });
}
void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}
