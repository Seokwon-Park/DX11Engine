#include "EnginePCH.h"
#include "EngineInputEvent.h"
#include <EnginePlatform/EngineInputSystem.h>




UEngineInputEvent::UEngineInputEvent()
{
}

UEngineInputEvent::~UEngineInputEvent()
{
}

void UEngineInputEvent::EventCheck(KeyCode _Key)
{
	if (true == UEngineInputSystem::GetKeyDown(_Key))
	{
		for (size_t i = 0; i < DownEvents.size(); i++)
		{
			DownEvents[i]();
		}
	}
	if (true == UEngineInputSystem::GetKey(_Key))
	{
		for (size_t i = 0; i < PressEvents.size(); i++)
		{
			PressEvents[i]();
		}
	}

	if (true == UEngineInputSystem::GetKeyFree(_Key))
	{
		for (size_t i = 0; i < FreeEvents.size(); i++)
		{
			FreeEvents[i]();
		}
	}

	if (true == UEngineInputSystem::GetKeyUp(_Key))
	{
		for (size_t i = 0; i < UpEvents.size(); i++)
		{
			UpEvents[i]();
		}
	}
}
