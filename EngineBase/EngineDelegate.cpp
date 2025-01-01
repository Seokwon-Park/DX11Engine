#include "EnginePCH.h"
#include "EngineDelegate.h"

UEngineDelegate::UEngineDelegate()
{
}

UEngineDelegate::UEngineDelegate(EventCallback _Function)
{
	Events.push_back(_Function);
}

UEngineDelegate::~UEngineDelegate()
{
}

UEngineDelegate::UEngineDelegate(const UEngineDelegate& _Other)
{
	Events = _Other.Events;
}

