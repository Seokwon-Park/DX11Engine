#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/Components/TilemapRendererComponent.h>
#include <EngineCore/Components/TilemapColliderComponent.h>

#include <EngineCore/Resources/EngineFont.h>

// Ό³Έν :
class ATilemapEditorGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATilemapEditorGameMode();
	~ATilemapEditorGameMode();

	// delete Function
	ATilemapEditorGameMode(const ATilemapEditorGameMode& _Other) = delete;
	ATilemapEditorGameMode(ATilemapEditorGameMode&& _Other) noexcept = delete;
	ATilemapEditorGameMode& operator=(const ATilemapEditorGameMode& _Other) = delete;
	ATilemapEditorGameMode& operator=(ATilemapEditorGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	EngineFont Font;
	std::shared_ptr<UTilemapComponent> TilemapComponent;
	std::shared_ptr<UTilemapRendererComponent> TilemapRenderer;
	std::shared_ptr<UTilemapColliderComponent> TilemapCollider;
};

