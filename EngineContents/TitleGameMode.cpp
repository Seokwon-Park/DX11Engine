#include "EnginePCH.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
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
	GetLevel()->SpawnActor<ATitleLogo>();

}
