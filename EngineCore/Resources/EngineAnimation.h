#pragma once

#include "EngineSprite.h"

class UEngineAnimation : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineAnimation();
	~UEngineAnimation();

	// Delete Function
	UEngineAnimation(const UEngineAnimation& _Other);
	UEngineAnimation(UEngineAnimation&& _Other) noexcept = delete;
	UEngineAnimation& operator=(const UEngineAnimation& _Other) = delete;
	UEngineAnimation& operator=(UEngineAnimation&& _Other) noexcept = delete;

	inline void Reset()
	{
		CurIndex = 0;
		CurTime = 0;
		ResultIndex = 0;
	}

	UEngineSprite* Sprite = nullptr;

	int CurIndex = 0;
	int ResultIndex = 0;
	float CurTime = 0.0f;
	bool IsLoop = true;
	std::vector<int> FrameIndices;
	std::vector<float> FrameIntervals;
	//Ư�� �����ӿ� ����Ǿ�� �� �̺�Ʈ
	//std::map<int, UEngineDelegate> Events;
};


