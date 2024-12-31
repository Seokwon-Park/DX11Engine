#include "EnginePCH.h"
#include "EngineKey.h"

void UEngineKey::KeyCheck(float _DeltaTime)
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