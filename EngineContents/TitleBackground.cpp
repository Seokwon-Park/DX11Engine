#include "EnginePCH.h"
#include "TitleBackground.h"

ATitleBackground::ATitleBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>();
	Sr->SetSprite("ui_mainpage_bg", 0);
	Sr->SetupAttachment(RootComponent);
}

ATitleBackground::~ATitleBackground()
{
}

void ATitleBackground::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
