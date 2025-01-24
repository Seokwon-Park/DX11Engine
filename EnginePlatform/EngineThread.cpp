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
	// 아직 ThreadInst 지금 돌고 있는 쓰레드라거 안된다.
	if (true == Thread.joinable())
	{
		return false;
	}

	if (nullptr == _Function)
	{
		MSGASSERT("함수를 세팅하지 않은 쓰레드는 start 할수 없습니다.");
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
