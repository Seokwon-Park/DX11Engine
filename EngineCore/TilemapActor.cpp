#include "EnginePCH.h"
#include "TilemapActor.h"

ATilemapActor::ATilemapActor()
{
	TilemapComponent = CreateDefaultSubobject<UTilemapComponent>();

	TilemapRendererComponent = CreateDefaultSubobject<UTilemapRendererComponent>();
	TilemapRendererComponent->SetTilemap(TilemapComponent);
	TilemapRendererComponent->SetOrder(ESortingLayer::BackgroundTilemap);
	TilemapRendererComponent->SetupAttachment(RootComponent);
}

ATilemapActor::~ATilemapActor()
{
}

void ATilemapActor::BeginPlay()
{
	AActor::BeginPlay();
}

void ATilemapActor::PlaySetup(std::string_view _TilemapName)
{
	TilemapComponent->Load(_TilemapName);
}

void ATilemapActor::EditSetup(std::string _SpriteName, FVector2 _TileSize, FVector2 _TilePivot)
{
	TilemapComponent->CreateNewTilemap(_SpriteName, _TileSize, _TilePivot);
}

void ATilemapActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
