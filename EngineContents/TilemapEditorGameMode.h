#pragma once
#include <EngineCore/GameMode.h>

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

};

