#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Components/SpriteRendererComponent.h>

// Ό³Έν :
class ATitleBackground : public AActor
{
public:
	// constrcuter destructer
	ATitleBackground();
	~ATitleBackground();

	// delete Function
	ATitleBackground(const ATitleBackground& _Other) = delete;
	ATitleBackground(ATitleBackground&& _Other) noexcept = delete;
	ATitleBackground& operator=(const ATitleBackground& _Other) = delete;
	ATitleBackground& operator=(ATitleBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<USpriteRendererComponent> Sr;
};

