#pragma once
#include <EngineCore/Actor.h>
#include "Components/CameraComponent.h"

// ���� :
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
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UCameraComponent> CameraComponent = nullptr;
};

