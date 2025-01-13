#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include <EngineCore/GUI/TilemapEditorWindow.h>
#include <EngineCore/Level.h>

#include "GridActor.h"


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
	Tilemap = CreateDefaultSubobject<UTilemapComponent>();
	Tilemap->SetTileSetting("Area0",FVector2(28, 28), FVector2(0.5f, 0.5f));

	TilemapRenderer = CreateDefaultSubobject<UTilemapRendererComponent>();
	TilemapRenderer->SetTilemap(Tilemap);
	TilemapRenderer->SetupAttachment(RootComponent);
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
