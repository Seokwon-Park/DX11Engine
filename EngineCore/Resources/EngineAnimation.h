#pragma once

#include "EngineSprite.h"
#include <EngineBase/EngineDelegate.h>

class UEngineAnimation : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineAnimation();
	~UEngineAnimation();

	// Delete Function
	UEngineAnimation(const UEngineAnimation& _Other) = delete;
	UEngineAnimation(UEngineAnimation&& _Other) noexcept = delete;
	UEngineAnimation& operator=(const UEngineAnimation& _Other) = delete;
	UEngineAnimation& operator=(UEngineAnimation&& _Other) noexcept = delete;

	inline void Reset()
	{
		CurIndex = 0;
		ResultIndex = 0;
	}

	UEngineSprite* Sprite = nullptr;

	int CurIndex = 0;
	int ResultIndex = 0;
	bool IsLoop = true;
	std::vector<int> FrameIndices;
	std::vector<float> FrameIntervals;
	//Ư�� �����ӿ� ����Ǿ�� �� �̺�Ʈ
	std::vector<UEngineDelegate> FrameEvents;
};


