#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class UBoxCollider2DComponent : public USceneComponent
{
public:
	// constrcuter destructer
	UBoxCollider2DComponent();
	~UBoxCollider2DComponent();

	// delete Function
	UBoxCollider2DComponent(const UBoxCollider2DComponent& _Other) = delete;
	UBoxCollider2DComponent(UBoxCollider2DComponent&& _Other) noexcept = delete;
	UBoxCollider2DComponent& operator=(const UBoxCollider2DComponent& _Other) = delete;
	UBoxCollider2DComponent& operator=(UBoxCollider2DComponent&& _Other) noexcept = delete;

protected:

private:

};

