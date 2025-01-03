#pragma once
#include "ActorComponent.h"
#include <EngineBase/EngineMath.h>

// 설명 :
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
		Transform.Location = _Value;
		UpdateTransform();
	}

	void AddLocation(const FVector4& _Value)
	{
		Transform.Location += _Value;
		UpdateTransform();
	}

	inline void AddRotation(const FVector4& _Rotation)
	{
		Transform.Rotation += _Rotation;
		UpdateTransform();
	}

	void SetRelativeScale3D(const FVector4& _Value)
	{
		Transform.Scale = _Value;
		UpdateTransform();
	}

	FTransform& GetTransformRef()
	{
		return Transform;
	}

	void GetParentTransform();

	ENGINE_API void SetupAttachment(std::shared_ptr<USceneComponent> _Parent);
	void SetupAttachment(USceneComponent* _Parent);

	//내가 업데이트 되면 자식도 업데이트 되어야한다.
	ENGINE_API void UpdateTransform();
protected:
	FTransform Transform;
private:
	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

