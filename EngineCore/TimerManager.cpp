#include "EnginePCH.h"
#include "TimerManager.h"

FTimerManager::FTimerManager()
{
}

FTimerManager::~FTimerManager()
{
}

void FTimerManager::SetTimer(EventFn _EventFn, float _DelayTime, bool _IsLoop)
{
	FTimeEvent Event;
	Event.Function = _EventFn;
	Event.CurTime = 0.0f;
	Event.DelayTime = _DelayTime;
	Event.IsLoop = _IsLoop;

	TimeEvents.push_back(Event);
}

void FTimerManager::Tick(float _DeltaTime)
{
	std::list<FTimeEvent>::iterator Iter = TimeEvents.begin();
	while (Iter != TimeEvents.end())
	{
		FTimeEvent& Event = *Iter;
		Event.CurTime += _DeltaTime;
		if (Event.CurTime >= Event.DelayTime)
		{
			Event.Function();
			if (Event.IsLoop == true)
			{
				Event.CurTime = 0.0f;
			}
			else
			{
				Iter = TimeEvents.erase(Iter);
				continue;
			}
		}
		Iter++;
	}


}
