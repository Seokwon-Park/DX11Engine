#include "EnginePCH.h"
#include "TestGameMode.h"
#include "Player.h"
#include "TitleLogo.h"

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::Tick(float _DeltaTime)
{
}

void ATestGameMode::BeginPlay()
{
	std::shared_ptr<ATitleLogo> Test = GetLevel()->SpawnActor<ATitleLogo>();
	Test->SetActorLocation({ 20.0f,0.0f,0.0f });
	//Logo->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });

	std::shared_ptr<APlayer> Player = GetLevel()->GetMainPawn<APlayer>();


	//std::shared_ptr<ATitleLogo> Logo2 = GetLevel()->SpawnActor<ATitleLogo>();
	//Logo2->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });
}

