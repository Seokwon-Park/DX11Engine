#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include "TilemapEditorWindow.h"
#include <EngineCore/Level.h>


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
}

ATilemapEditorGameMode::~ATilemapEditorGameMode()
{
}

void ATilemapEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	GetLevel()->AddGuiWindow(std::make_shared<UTilemapEditorWindow>(GetLevel()));
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
