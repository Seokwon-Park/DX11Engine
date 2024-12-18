#include "EnginePCH.h"	
#include "ActorComponent.h"

UActorComponent::UActorComponent()
{
}

UActorComponent::~UActorComponent()
{
}

std::shared_ptr<class AActor> UActorComponent::GetOwner()
{
	return Owner;
}