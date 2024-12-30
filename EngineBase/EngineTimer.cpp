#include "EnginePCH.h"
#include "EngineTimer.h"


UEngineTimer::UEngineTimer()
{
	PrevTime = Clock::now();
}

UEngineTimer::~UEngineTimer()
{
}

void UEngineTimer::TimeReset()
{
	PrevTime = Clock::now();
}

//float UEngineTimer::End()
//{
//	TimeCheck();
//	return GetDeltaTime();
//}
//
//double UEngineTimer::DEnd()
//{
//	TimeCheck();
//	return GetDoubleDeltaTime();
//}

void UEngineTimer::TimeCheck()
{
	 CurrentTime = Clock::now();
	DeltaTime = std::chrono::duration_cast<Duration>(CurrentTime - PrevTime).count();
	PrevTime = CurrentTime;
}
