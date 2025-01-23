#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/Components/TilemapRendererComponent.h>
#include "GroundTilemap.h"

#include <EngineCore/Resources/EngineFont.h>

//temp
#include <EngineCore/Components/TextRendererComponent.h>


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
	std::shared_ptr<AGroundTilemap> GroundTilemap;
	std::shared_ptr<ATilemapActor> BackgroundTilemap;
	std::shared_ptr<UTextRendererComponent> Tr;

};

