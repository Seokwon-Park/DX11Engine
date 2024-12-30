#include "EnginePCH.h"
#include "EngineInputSystem.h"


void UEngineInputSystem::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (0 != GetAsyncKeyState(Key))
	{
		PressTime += _DeltaTime;
		if (true == IsFree)
		{
			IsDown = true;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}
		else if (true == IsDown)
		{
			IsDown = false;
		}
	}
	else
	{
		PressTime = 0.0f;
		if (true == IsPress)
		{
			IsUp = true;
			IsPress = false;
			IsFree = true;
		}
		else if (true == IsUp)
		{
			IsUp = false;
		}
	}
}

UEngineInputSystem::UEngineInputSystem()
{
	for (int i = 0; i < 255; i++)
	{
		Keys.insert(std::make_pair(i, UEngineKey(i)));
	}
}

UEngineInputSystem::~UEngineInputSystem()
{
}

void UEngineInputSystem::KeyCheck(float _DeltaTime)
{
	//std::cout << GetInstance().Keys[EKey::Left].IsDown<< '\n';
	for (auto& Itr : GetInstance().Keys)
	{
		UEngineKey& CurKey = Itr.second;
		CurKey.KeyCheck(_DeltaTime);
	}
}



