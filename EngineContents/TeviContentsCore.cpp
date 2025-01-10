#include "EnginePCH.h"
#include "TeviContentsCore.h"
#include "EngineCore/Level.h"
#include "EngineCore/EngineCore.h"
#include <EngineCore/Pawn.h>
#include <EngineCore/GameMode.h>
#include <EngineCore/ResourceManager.h>
#include <EngineBase/EngineIO.h>

#include "TitleGameMode.h"
#include "TestGameMode.h"
#include "TileMapEditorGameMode.h"
#include "Player.h"

CreateContentsCoreDefine(UTeviContentsCore);

UTeviContentsCore::UTeviContentsCore()
{
}

UTeviContentsCore::~UTeviContentsCore()
{
}

void UTeviContentsCore::EngineStart(UEngineInitData& _Data)
{
	// 윈도우 크기 지정
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	UResourceManager::LoadResourcesFromDirectory<UEngineTexture2D>({ ".PNG" }, "Images");

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/Tevi");

	auto Sprite = UEngineSprite::CreateSpriteFromFolder(Dir.ToString());
	Sprite->SetPivot(EPivotType::Center);

	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/Area0");
	Sprite = UEngineSprite::CreateSpriteFromFolder(Dir.ToString());
	Sprite->SetPivot(EPivotType::Center);

	//Sprite->SetPivot(FVector2(0.05f, 0.0f), 2);
	//Sprite->SetPivot(FVector2(0.06f, 0.0f), 3);
	UEngineAnimation::CreateAnimation("TeviIdle", "Tevi", 0,3, 0.1f);
	UEngineAnimation::CreateAnimation("TeviWalk", "Tevi", 4, 9, 0.2f);
	UEngineAnimation::CreateAnimation("TeviRun", "Tevi", 11, 16, 0.1f);
	UEngineAnimation::CreateAnimation("TeviJump", "Tevi", 20, 24, 0.1f, false);

	UEngineCore::CreateLevel<ATitleGameMode, APlayer>("Title");
	UEngineCore::CreateLevel<ATestGameMode, APlayer>("Test");
	UEngineCore::CreateLevel<ATilemapEditorGameMode, APlayer>("TilemapEditor");
	UEngineCore::OpenLevel("TilemapEditor");
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}