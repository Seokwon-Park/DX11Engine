#include "EnginePCH.h"
#include "FontAtlasEditorGameMode.h"
#include <EngineCore/GUI/TextAtlasEditorWindow.h>

AFontAtlasEditorGameMode::AFontAtlasEditorGameMode()
{
	Tr = CreateDefaultSubobject<UTextRendererComponent>();
	Tr->SetupAttachment(RootComponent);
	
	
}

AFontAtlasEditorGameMode::~AFontAtlasEditorGameMode()
{
}

void AFontAtlasEditorGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Font");
	UEngineFile File = Dir.GetFile("NanumGothic.ttf");

	UEngineFont::Create(File);

	Tr->SetFont("NanumGothic");
	Tr->SetText("Test");

	SetActorRelativeScale3D({ 10.0f,10.0f, 1.0f, 1.0f });

	std::shared_ptr<UTextAtlasEditorWindow> Window = std::make_shared<UTextAtlasEditorWindow>();
	GetLevel()->AddGuiWindow(Window);
}

void AFontAtlasEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
}
