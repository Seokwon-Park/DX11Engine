#include "EnginePCH.h"
#include "GroundTilemap.h"

AGroundTilemap::AGroundTilemap()
{
	TilemapColliderComponent = CreateDefaultSubobject<UTilemapColliderComponent>();
	TilemapColliderComponent->SetTilemap(TilemapComponent);
	TilemapRendererComponent->SetOrder(ESortingLayer::GroundTilemap);
	TilemapColliderComponent->SetupAttachment(RootComponent);
}

AGroundTilemap::~AGroundTilemap()
{
}

void AGroundTilemap::BeginPlay()
{
	ATilemapActor::BeginPlay();
}

void AGroundTilemap::Tick(float _DeltaTime)
{
	ATilemapActor::Tick(_DeltaTime);
}
