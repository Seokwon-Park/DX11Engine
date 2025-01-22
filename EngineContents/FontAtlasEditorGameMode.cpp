#include "EnginePCH.h"
#include "FontAtlasEditorGameMode.h"
#include <EngineCore/GUI/TextAtlasEditorWindow.h>

int AFontAtlasEditorGameMode::x = 0;
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
	Dir.AppendDirectory("Fonts");
	UEngineFile File = Dir.GetFile("NanumGothic.ttf");

	UEngineFont::Create("NanumGothic", Dir);

	Tr->SetFont("NanumGothic");

	SetActorLocation({ -500.0f, 0.0f, 0.0f, 1.0f });

	std::shared_ptr<UTextAtlasEditorWindow> Window = std::make_shared<UTextAtlasEditorWindow>();
	GetLevel()->AddGuiWindow(Window);
}

void AFontAtlasEditorGameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);
	x++;
	Tr->SetText(std::to_string(x));
}
