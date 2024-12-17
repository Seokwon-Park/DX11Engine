#include "EnginePCH.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
	GetLevel()->SpawnActor<ATitleLogo>();
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
void ATitleGameMode::BeginPlay()
{
	AActor::BeginPlay();
}
