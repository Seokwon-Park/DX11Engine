#include "EnginePCH.h"
#include "EngineThread.h"
#include <EngineBase/EngineString.h>


UEngineThread::UEngineThread()
{
}

UEngineThread::~UEngineThread()
{
	Join();
}

bool UEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	// ���� ThreadInst ���� ���� �ִ� �������� �ȵȴ�.
	if (true == Thread.joinable())
	{
		return false;
	}

	if (nullptr == _Function)
	{
		MSGASSERT("�Լ��� �������� ���� ������� start �Ҽ� �����ϴ�.");
		return false;
	}

	Name = _Name;
	ThreadFunction = _Function;
	Thread = std::thread(std::bind(ThreadBaseFunction, this));
	return true;
}

void UEngineThread::Join()
{
}

void UEngineThread::ThreadBaseFunction(UEngineThread* _Thread)
{
	std::wstring WName = UEngineString::ToWideString(_Thread->Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());

	_Thread->ThreadFunction();
}
