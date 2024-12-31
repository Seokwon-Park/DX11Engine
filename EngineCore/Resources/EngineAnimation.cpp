#include "EnginePCH.h"
#include "EngineAnimation.h"

UEngineAnimation::UEngineAnimation()
{
}

UEngineAnimation::~UEngineAnimation()
{
}

UEngineAnimation::UEngineAnimation(const UEngineAnimation& _Other)
{
	Sprite = _Other.Sprite;

	CurIndex = _Other.CurIndex;
	ResultIndex = _Other.ResultIndex;
	CurTime = _Other.CurTime;
	IsLoop = _Other.IsLoop;
	FrameIndices = _Other.FrameIndices;
	FrameIntervals = _Other.FrameIntervals;
}
