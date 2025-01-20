#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/Resources/EngineFont.h>

//temp
#include <EngineCore/Components/TextRendererComponent.h>

// Ό³Έν :
class AFontAtlasEditorGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AFontAtlasEditorGameMode();
	~AFontAtlasEditorGameMode();

	// delete Function
	AFontAtlasEditorGameMode(const AFontAtlasEditorGameMode& _Other) = delete;
	AFontAtlasEditorGameMode(AFontAtlasEditorGameMode&& _Other) noexcept = delete;
	AFontAtlasEditorGameMode& operator=(const AFontAtlasEditorGameMode& _Other) = delete;
	AFontAtlasEditorGameMode& operator=(AFontAtlasEditorGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UTextRendererComponent> Tr;

};

