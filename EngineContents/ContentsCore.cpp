#include "EnginePCH.h"
#include "ContentsCore.h"

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

	// ������ ũ�� ����
}

void UTeviContentsCore::EngineTick(float _DeltaTime)
{

}

void UTeviContentsCore::EngineEnd()
{

}