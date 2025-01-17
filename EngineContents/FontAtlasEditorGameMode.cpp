#include "EnginePCH.h"
#include "FontAtlasEditorGameMode.h"

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

	UEngineFont::Create(File);
}

void AFontAtlasEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
