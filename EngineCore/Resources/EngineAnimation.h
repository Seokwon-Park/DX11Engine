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

	// 스프라이트의 인덱스 범위를 기반으로 애니메이션을 생성
	ENGINE_API static void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		int _StartFrame, int _EndFrame, float _FrameInterval = 0.1f, bool _IsLoop = true);
	ENGINE_API static void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _Indices, float _FrameInterval, bool _IsLoop = true);
	ENGINE_API static void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _FrameIndices, std::vector<float> _FrameIntervals, bool _IsLoop = true);

	UEngineSprite* Sprite = nullptr;

	int CurIndex = 0;
	int ResultIndex = 0;
	bool IsLoop = true;
	std::vector<int> FrameIndices;
	std::vector<float> FrameIntervals;
	//특정 프레임에 실행되어야 할 이벤트
	std::vector<UEngineDelegate> FrameEvents;
};


