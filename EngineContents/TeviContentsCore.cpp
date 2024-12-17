#include "EnginePCH.h"
#include "TeviContentsCore.h"
#include "EngineCore/Level.h"
#include "EngineCore/EngineCore.h"
#include <EngineCore/Pawn.h>
#include <EngineCore/GameMode.h>

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
	// mainwindow�� �ƹ��� �ǵ�� �ȵȴ�.
	// �� �������ݾ� ������ �����ϴ� �������°� �����ϴ����� ������Ѵ�.

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel<ATitleGameMode, APlayer>("Titlelevel");
	// UEngineCore::OpenLevel("Titlelevel");
	//UEngineCore::OpenLevel("fasdfasdfasd");
	//std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel<>();

	// ������ ũ�� ����
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}