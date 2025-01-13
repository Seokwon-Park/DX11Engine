#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Components/GridRendererComponent.h>

class AGridActor : public AActor
{
public:
	// constrcuter destructer
	AGridActor();
	~AGridActor();

	// delete Function
	AGridActor(const AGridActor& _Other) = delete;
	AGridActor(AGridActor&& _Other) noexcept = delete;
	AGridActor& operator=(const AGridActor& _Other) = delete;
	AGridActor& operator=(AGridActor&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UGridRendererComponent> GridRenderer;

};

