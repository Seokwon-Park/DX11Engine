#include "EnginePCH.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "Player.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//std::shared_ptr<APlayer> Player = GetLevel()->GetMainPawn<APlayer>();
	//Player->AddActorLocation(FVector4::LEFT*_DeltaTime);
}
void ATitleGameMode::BeginPlay()
{
	AActor::BeginPlay();

	std::shared_ptr<ATitleLogo> Logo = GetLevel()->SpawnActor<ATitleLogo>();
	Logo->SetActorLocation({ 5.0f,0.0f,0.0f });
	Logo->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });

	std::shared_ptr<APlayer> Player = GetLevel()->GetMainPawn<APlayer>();
	Player->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });


	//std::shared_ptr<ATitleLogo> Logo2 = GetLevel()->SpawnActor<ATitleLogo>();
	//Logo2->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });


}
