#include "EnginePCH.h"
#include "TeviContentsCore.h"
#include "EngineCore/Level.h"
#include "EngineCore/EngineCore.h"

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

	//std::shared_ptr<ULevel> Level = UEngineCore::CreateLevel<>();

	// ������ ũ�� ����
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}