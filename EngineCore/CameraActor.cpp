#include "EnginePCH.h"
#include "CameraActor.h"
#include "EngineCore.h"

ACameraActor::ACameraActor()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>();

	RootComponent = CameraComponent;
}

ACameraActor::~ACameraActor()
{
}

void ACameraActor::BeginPlay()
{
	AActor::BeginPlay();
}

FIntPoint ACameraActor::GetWorldMousePos()
{
	return CameraComponent->ScreenToWorld(UEngineCore::GetMainWindow().GetMousePos());
}

void ACameraActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (Target != nullptr)
	{
		SetActorLocation(Target->GetActorLocation());
	}

	CameraComponent->CalculateView();
	CameraComponent->CalculateProj();
}
