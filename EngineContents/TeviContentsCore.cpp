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
	_Data.WindowSize = { 300, 300 };

<<<<<<< HEAD
	std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel<TitleGameMode>();
=======
	UEngineCore::CreateLevel<AGameMode, APawn>("Titlelevel");
	// UEngineCore::OpenLevel("Titlelevel");
	UEngineCore::OpenLevel("fasdfasdfasd");
	//std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel<>();
>>>>>>> e303e6160b12585f4d905ed7f018109223275f16

	// ������ ũ�� ����
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}