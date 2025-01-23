#include "EnginePCH.h"
#include "TestGameMode.h"
#include "Player.h"
#include "TitleLogo.h"

ATestGameMode::ATestGameMode()
{
	//Tilemap = CreateDefaultSubobject<UTilemapComponent>();
	////Tilemap->Load("11");
	//TilemapRenderer = CreateDefaultSubobject<UTilemapRendererComponent>();
	//TilemapRenderer->SetupAttachment(RootComponent);
	//TilemapRenderer->SetTilemap(Tilemap);
	//TilemapCollider = CreateDefaultSubobject<UTilemapColliderComponent>();
	//TilemapCollider->SetupAttachment(RootComponent);
	//TilemapCollider->SetTilemap(Tilemap);
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}

void ATestGameMode::BeginPlay()
{
	AGameMode::BeginPlay();
	//UEngineDirectory Dir;
	//if (false == Dir.MoveParentToDirectory("Resources"))
	//{
	//	MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
	//	return;
	//}
	//Dir.AppendDirectory("TilemapData");

	//UEngineFile NewFile = Dir.GetFile("Testmap.Tmap");
	//UEngineSerializer Ser;

	//NewFile.FileOpen("rb");
	//NewFile.Read(Ser);

	//Tilemap->DeSerialize(Ser);

	/*std::shared_ptr<ATitleLogo> Test = GetLevel()->SpawnActor<ATitleLogo>("Test Tevi");
	Test->SetActorLocation({ 0.0f,-100.0f,0.0f,1.0f });*/
	//Logo->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });

	std::shared_ptr<APlayer> Player = GetLevel()->GetMainPawn<APlayer>();


	//std::shared_ptr<ATitleLogo> Logo2 = GetLevel()->SpawnActor<ATitleLogo>();
	//Logo2->SetActorRelativeScale3D({ 100.0f,100.0f,1.0f });
}

