#include "EnginePCH.h"
#include "Actor.h"
#include "SceneComponent.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::SetActorLocation(const FVector4& _Value)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	//RootComponent->SetComponentLocation(_Value);
}

void AActor::AddActorLocation(const FVector4& _Value)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	//RootComponent->AddComponentLocation(_Value);
}

void AActor::BeginPlay()
{
	if (nullptr != RootComponent)
	{
		RootComponent->BeginPlay();
	}
}


void AActor::Tick(float _DeltaTime)
{
}

