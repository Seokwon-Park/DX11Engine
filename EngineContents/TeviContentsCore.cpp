#include "EnginePCH.h"
#include "TeviContentsCore.h"
#include "EngineCore/Level.h"
#include "EngineCore/EngineCore.h"
#include <EngineCore/Pawn.h>
#include <EngineCore/GameMode.h>
#include <EngineCore/ResourceManager.h>
#include <EngineBase/EngineIO.h>

#include "TitleGameMode.h"
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
	UEngineSprite::CreateSpriteFromFolder(Dir.ToString());

	UEngineCore::CreateLevel<ATitleGameMode, APlayer>("Titlelevel");
	UEngineCore::OpenLevel("Titlelevel");
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}