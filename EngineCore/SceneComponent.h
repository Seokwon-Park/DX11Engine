#pragma once
#include "ActorComponent.h"
#include <EngineBase/EngineMath.h>

// Ό³Έν :
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

	inline void SetLocation(const FVector4& _Value)
	{
		Transform.Translation = _Value;
	}

	FTransform& GetTransformRef()
	{
		return Transform;
	}
protected:
	FTransform Transform;
private:
	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

