#include "EnginePCH.h"
#include "TilemapEditorGameMode.h"
#include <EngineCore/GUI/TilemapEditorWindow.h>
#include <EngineCore/Level.h>

#include "GridActor.h"


ATilemapEditorGameMode::ATilemapEditorGameMode()
{
	TilemapComponent = CreateDefaultSubobject<UTilemapComponent>();
	TilemapComponent->CreateNewTilemap("Area0",FVector2(28, 28), FVector2(0.5f, 0.5f));

	TilemapRenderer = CreateDefaultSubobject<UTilemapRendererComponent>();
	TilemapRenderer->SetTilemap(TilemapComponent);
	TilemapRenderer->SetupAttachment(RootComponent);

	TilemapCollider = CreateDefaultSubobject<UTilemapColliderComponent>();
	TilemapCollider->SetTilemap(TilemapComponent);
	TilemapCollider->SetupAttachment(RootComponent);
}

ATilemapEditorGameMode::~ATilemapEditorGameMode()
{
}

void ATilemapEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	/*TilemapComponent->Load("111");
	TilemapCollider->UpdateCollider();*/
	std::shared_ptr<UTilemapEditorWindow> Window = std::make_shared<UTilemapEditorWindow>(GetLevel());
	Window->SetTilemap(TilemapComponent);
	Window->SetTilemapCollider(TilemapCollider);
	GetLevel()->AddGuiWindow(Window);
	GetLevel()->SpawnActor<AGridActor>();
}

void ATilemapEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);

}
