#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include "TilemapEditorWindow.h"
#include <EngineCore/Level.h>


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
	Tilemap = CreateDefaultSubobject<UTilemapRendererComponent>();
	Tilemap->SetTileSetting("Area0", { 28,28 }, {0.5f, 0.5f});
	Tilemap->SetupAttachment(RootComponent);
}

ATilemapEditorGameMode::~ATilemapEditorGameMode()
{
}

void ATilemapEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();
	auto Window = std::make_shared<UTilemapEditorWindow>(GetLevel());
	Window->TilemapRenderer = Tilemap.get();
	GetLevel()->AddGuiWindow(Window);
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
