#include "EnginePCH.h"
#include "FontAtlasEditorGameMode.h"
#include <EngineCore/GUI/TextAtlasEditorWindow.h>

AFontAtlasEditorGameMode::AFontAtlasEditorGameMode()
{
}

AFontAtlasEditorGameMode::~AFontAtlasEditorGameMode()
{
}

void AFontAtlasEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources");
	UEngineFile File = Dir.GetFile("NanumGothic.ttf");

	std::shared_ptr<UTextAtlasEditorWindow> Window = std::make_shared<UTextAtlasEditorWindow>();
	GetLevel()->AddGuiWindow(Window);

	//UEngineFont::Create(File);
}

void AFontAtlasEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
