#include "EnginePCH.h"
#include "Actor.h"
#include "Components/SceneComponent.h"
#include "Components/DefaultSceneComponent.h"
#include "Level.h"


AActor::AActor()
{
	RootComponent = CreateDefaultSubobject<UDefaultSceneComponent>();
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

	RootComponent->SetLocation(_Value);
}

void AActor::AddActorLocation(const FVector4& _Value)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	RootComponent->AddLocation(_Value);
}

 void AActor::SetActorRotation(const FVector4& _Rotation)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	RootComponent->SetRotation(_Rotation);
}

void AActor::AddActorRotation(const FVector4& _Rotation)
{
	if (nullptr == RootComponent)
	{
		return;
	}

	RootComponent->AddRotation(_Rotation);
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

	for (std::shared_ptr<class UActorComponent>& ActorComponent : ActorComponentList)
	{
		ActorComponent->BeginPlay();
	}
}


void AActor::Tick(float _DeltaTime)
{
	if (nullptr != RootComponent)
	{
		RootComponent->TickComponent(_DeltaTime);
	}

	for (std::shared_ptr<class UActorComponent>& ActorComponent : ActorComponentList)
	{
		ActorComponent->TickComponent(_DeltaTime);
	}
}

