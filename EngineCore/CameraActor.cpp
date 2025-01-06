#include "EnginePCH.h"
#include "CameraActor.h"

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

void ACameraActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CameraComponent->CalculateView();
	CameraComponent->CalculateProj();
}
