#include "EnginePCH.h"
#include "GridActor.h"
#include <EngineCore/Resources/EngineMaterial.h>

AGridActor::AGridActor()
{
	GridRenderer = CreateDefaultSubobject<UGridRendererComponent>();
	GridRenderer->SetRelativeScale3D(FVector4(30000000.0, 30000000.0, 1.0f, 1.0f));
	GridRenderer->SetOrder(ESortingLayer::Default, -10);

	GridRenderer->SetupAttachment(RootComponent);

}

AGridActor::~AGridActor()
{
}

void AGridActor::BeginPlay()
{
	AActor::BeginPlay();
}

void AGridActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
