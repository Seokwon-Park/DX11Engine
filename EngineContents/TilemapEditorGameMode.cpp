#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include <EngineCore/GUI/TilemapEditorWindow.h>
#include <EngineCore/Level.h>

#include "Player.h"
#include "GridActor.h"


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
	Tr = CreateDefaultSubobject<UTextRendererComponent>();
	//Tr->SetupAttachment(RootComponent);


}

ATilemapEditorGameMode::~ATilemapEditorGameMode()
{
}

void ATilemapEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	GetLevel()->GetCurrentCamera()->SetTarget(GetLevel()->GetMainPawn<APlayer>());

	GroundTilemap = GetLevel()->SpawnActor<AGroundTilemap>("Ground");
	GroundTilemap->EditSetup("Area0", { 28.0f,28.0f }, {0.5f,0.5f});
	BackgroundTilemap = GetLevel()->SpawnActor<AGroundTilemap>("Background");
	BackgroundTilemap->EditSetup("Backdrop0", { 28.0f,28.0f }, { 0.5f,0.5f });

	Tr->SetFont("NanumGothic");
	Tr->SetText("¾È³çÇÏ¼¼¿ä");
	/*TilemapCollider->UpdateCollider(); */
	std::shared_ptr<UTilemapEditorWindow> Window = std::make_shared<UTilemapEditorWindow>(GetLevel());
	Window->AddTilemapList(GroundTilemap);
	Window->AddTilemapList(BackgroundTilemap);
	GetLevel()->AddGuiWindow(Window);
	GetLevel()->SpawnActor<AGridActor>("Grid");
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);

}
