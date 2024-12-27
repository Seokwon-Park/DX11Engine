#include "EnginePCH.h"
#include "Actor.h"
#include "Components/SceneComponent.h"

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

	RootComponent->AddLocation(_Value);
}

void AActor::SetActorRelativeScale3D(const FVector4& _Scale)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	RootComponent->SetRelativeScale3D(_Scale);
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

