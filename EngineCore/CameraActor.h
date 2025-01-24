#pragma once
#include <EngineCore/Actor.h>
#include "Components/CameraComponent.h"

// Ό³Έν :
class ACameraActor : public AActor
{
public:
	// constrcuter destructer
	ACameraActor();
	~ACameraActor();

	// delete Function
	ACameraActor(const ACameraActor& _Other) = delete;
	ACameraActor(ACameraActor&& _Other) noexcept = delete;
	ACameraActor& operator=(const ACameraActor& _Other) = delete;
	ACameraActor& operator=(ACameraActor&& _Other) noexcept = delete;

	inline std::shared_ptr<UCameraComponent> GetCameraComponent() { return CameraComponent; }
	inline void SetTarget(std::shared_ptr<AActor> _Target) { SetTarget(_Target.get()); }
	inline void SetTarget(AActor* _Target) { Target = _Target; }

	ENGINE_API FIntPoint GetWorldMousePos();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	AActor* Target;
	std::shared_ptr<UCameraComponent> CameraComponent = nullptr;
};

