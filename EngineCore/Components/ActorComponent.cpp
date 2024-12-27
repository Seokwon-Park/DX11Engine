#include "EnginePCH.h"	
#include "ActorComponent.h"

UActorComponent::UActorComponent()
{
}

UActorComponent::~UActorComponent()
{
}

AActor* UActorComponent::GetOwner()
{
	return Owner;
}