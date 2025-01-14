#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include <EngineCore/GUI/TilemapEditorWindow.h>
#include <EngineCore/Level.h>

#include "GridActor.h"


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
	Tilemap = CreateDefaultSubobject<UTilemapComponent>();
	Tilemap->SetTileSetting("Area0",FVector2(28, 28), FVector2(0.5f, 0.5f));

	//UEngineDirectory Dir;
	//if (false == Dir.MoveParentToDirectory("Resources"))
	//{
	//	MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//	return;
	//}
	//Dir.AppendDirectory("TilemapData");

	//UEngineFile NewFile = Dir.GetFile("Testmap.Tmap");
	//UEngineSerializer Ser;

	//NewFile.FileOpen("rb");
	//NewFile.Read(Ser);

	//Tilemap->DeSerialize(Ser);

	TilemapRenderer = CreateDefaultSubobject<UTilemapRendererComponent>();
	TilemapRenderer->SetTilemap(Tilemap);
	TilemapRenderer->SetupAttachment(RootComponent);

	TilemapCollider = CreateDefaultSubobject<UTilemapColliderComponent>();
	TilemapCollider->SetTilemap(Tilemap);
	TilemapCollider->SetupAttachment(RootComponent);
}

ATilemapEditorGameMode::~ATilemapEditorGameMode()
{
}

void ATilemapEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();
	std::shared_ptr<UTilemapEditorWindow> Window = std::make_shared<UTilemapEditorWindow>(GetLevel());
	Window->SetTilemap(Tilemap);
	GetLevel()->AddGuiWindow(Window);

	GetLevel()->SpawnActor<AGridActor>();
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
