#include "EnginePCH.h"
#include "TitleBackground.h"
#include <EngineCore/EngineCore.h>

ATitleBackground::ATitleBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>();
	Sr->SetSprite("ui_mainpage_bg", 0);
	Sr->SetupAttachment(RootComponent);
	Sr->SetAutoScale(false);
	Sr->SetRelativeScale3D({UEngineCore::GetMainWindow().GetWindowSize().X, UEngineCore::GetMainWindow().GetWindowSize().Y});
	
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
