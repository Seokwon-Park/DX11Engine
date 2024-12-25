#pragma once
#include "ActorComponent.h"
#include <EngineBase/EngineMath.h>

// ���� :
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	virtual ~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

protected:

private:
	FTransform Transform;

	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

