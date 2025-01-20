#include "EnginePCH.h"
#include "EngineThread.h"


UEngineThread::UEngineThread()
{
}

UEngineThread::~UEngineThread()
{
}

bool UEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	return false;
}

void UEngineThread::Join()
{
}

void UEngineThread::ThreadBaseFunction(UEngineThread* _Thread)
{
}
