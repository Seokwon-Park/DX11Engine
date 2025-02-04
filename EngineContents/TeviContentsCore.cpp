#include "EnginePCH.h"
#include "TeviContentsCore.h"
#include "EngineCore/Level.h"
#include "EngineCore/EngineCore.h"
#include <EngineCore/Pawn.h>
#include <EngineCore/GameMode.h>
#include <EngineCore/ResourceManager.h>
#include <EngineCore/EnginePhysics.h>
#include <EngineBase/EngineIO.h>

#include "TitleGameMode.h"
#include "TestGameMode.h"
#include "TilemapEditorGameMode.h"
#include "FontAtlasEditorGameMode.h"
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
	// ������ ũ�� ����
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	UResourceManager::LoadResourcesFromDirectory<UEngineTexture2D>({ ".PNG" }, "Images");
	UResourceManager::LoadResourcesFromDirectory<UEngineTilemap>({ ".Tmap" }, "TilemapData");

	// ���� : ������ Texture�� ���� �ε��ǵ��� �� ��.
	UResourceManager::LoadResourcesFromDirectory<UEngineTexture2D>({ ".PNG" }, "Fonts");
	UResourceManager::LoadResourcesFromDirectory<UEngineFont>({ ".ttf" }, "Fonts");

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/Tevi");
	auto Sprite = UEngineSprite::CreateSpriteFromFolderSorted(Dir.ToString(), std::regex(R"(([a-zA-Z]+)(\d*)_n_(\d+).png)"));
	Sprite->SetPivot(EPivotType::Center);

	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/TeviEffect");
	Sprite = UEngineSprite::CreateSpriteFromFolderSorted(Dir.ToString(), std::regex(R"(([a-zA-Z]+)(\d*)_e_(\d+).png)"));
	Sprite->SetPivot(EPivotType::Center);

	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/Area0");
	Sprite = UEngineSprite::CreateSpriteFromFolder(Dir.ToString());
	Sprite->SetPivot(EPivotType::Center);

	Dir.MoveParentToDirectory("Resources");
	Dir.AppendDirectory("Images/Backdrop0");
	Sprite = UEngineSprite::CreateSpriteFromFolder(Dir.ToString());
	Sprite->SetPivot(EPivotType::Center);

	//Sprite->SetPivot(FVector2(0.05f, 0.0f), 2);
	//Sprite->SetPivot(FVector2(0.06f, 0.0f), 3);
	UEngineAnimation::CreateAnimation("TeviIdle", "Tevi", 0, 3, 0.1f);
	UEngineAnimation::CreateAnimation("TeviWalk", "Tevi", 4, 9, 0.2f);
	UEngineAnimation::CreateAnimation("TeviRun", "Tevi", 11, 16, 0.1f);
	UEngineAnimation::CreateAnimation("TeviJump", "Tevi", 20, 24, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAir", "Tevi", 25, 27, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAttack", "Tevi", 0, 0, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAttack0", "Tevi", 250, 255, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAttack1", "Tevi", 256, 259, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAttack2", "Tevi", 200, 206, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviAttack3", "Tevi", { 226,227,329,330,331,332,333,334,335 }, 0.1f, false);

	UEngineAnimation::CreateAnimation("TeviGroundAttackEffect0", "TeviEffect", 250, 255, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviGroundAttackEffect1", "TeviEffect", 256, 259, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviGroundAttackEffect2", "TeviEffect", 200, 206, 0.1f, false);
	UEngineAnimation::CreateAnimation("TeviGroundAttackEffect3", "TeviEffect", { 226,227,309,310,311,312,313,314,315 }, 0.1f, false);



	UEnginePhysics::CollisionRule[Player] = Ground;
	UEnginePhysics::CollisionRule[Ground] = Player;

	UEngineCore::CreateLevel<ATitleGameMode, APlayer>("Title");
	UEngineCore::CreateLevel<ATestGameMode, APlayer>("Test");
	UEngineCore::CreateLevel<ATilemapEditorGameMode, APlayer>("TilemapEditor");
	UEngineCore::CreateLevel<AFontAtlasEditorGameMode, APawn>("TextAtlasEditor");
	//UEngineCore::OpenLevel("Title");
	//ngineCore::OpenLevel("Test");
	//UEngineCore::OpenLevel("TilemapEditor");
	UEngineCore::OpenLevel("TextAtlasEditor");
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}