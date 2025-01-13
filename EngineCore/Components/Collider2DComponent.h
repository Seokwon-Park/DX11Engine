#pragma once
#include "SceneComponent.h"
#include <EngineCore/Enums/EngineLayer.h>
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>

// Ό³Έν :
class UCollider2DComponent : public USceneComponent
{
public:
	// constrcuter destructer
	UCollider2DComponent();
	~UCollider2DComponent();

	// delete Function
	UCollider2DComponent(const UCollider2DComponent& _Other) = delete;
	UCollider2DComponent(UCollider2DComponent&& _Other) noexcept = delete;
	UCollider2DComponent& operator=(const UCollider2DComponent& _Other) = delete;
	UCollider2DComponent& operator=(UCollider2DComponent&& _Other) noexcept = delete;

	ENGINE_API virtual void DebugRender(class UCameraComponent* _Camera, float _DeltaTime) = 0;
	virtual void TickComponent(float _DeltaTime) override;
	inline void SetCollisionLayer(ECollisionLayer _Layer) { Layer = _Layer; }

protected:
	virtual void BeginPlay() override;

	ECollisionLayer Layer;
private:

};

