#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include "TilemapEditorWindow.h"
#include <EngineCore/Level.h>


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
	auto Window = std::make_shared<UTilemapEditorWindow>(GetLevel());
	Window->Tilemap = Tilemap.get();
	GetLevel()->AddGuiWindow(Window);
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
