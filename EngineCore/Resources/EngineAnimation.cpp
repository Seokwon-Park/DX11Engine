#include "EnginePCH.h"
#include "EngineAnimation.h"
#include "ResourceManager.h"

UEngineAnimation::UEngineAnimation()
{
}

UEngineAnimation::~UEngineAnimation()
{
}

void UEngineAnimation::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	int _StartFrame, int _EndFrame, float _FrameInterval, bool _IsLoop)
{
	if (_StartFrame > _EndFrame)
	{
		MSGASSERT(std::string(_AnimationName) + "잘못된 범위 설정. FrameStart가 FrameEnd보다 큽니다.");
		return;
	}

	int Size = (_EndFrame - _StartFrame) + 1;

	std::vector<int> Indices;
	std::vector<float> Intervals(Size, _FrameInterval);

	for (int i = 0; i < Size; i++)
	{
		Indices.push_back(_StartFrame + i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Indices, Intervals, _IsLoop);
}

void UEngineAnimation::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _Indices, float _FrameInterval, bool _IsLoop)
{
	std::vector<float> Intervals(_Indices.size(), _FrameInterval);

	CreateAnimation(_AnimationName, _SpriteName, _Indices, Intervals, _IsLoop);
}

void UEngineAnimation::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _FrameIndices, std::vector<float> _FrameIntervals, bool _IsLoop)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_FrameIndices.size() != _FrameIntervals.size())
	{
		MSGASSERT("두 배열 인자의 크기가 다릅니다. _Index와 _Interval의 크기가 동일해야 합니다.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UResourceManager::Find<UEngineSprite>(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 애니메이션 생성에 사용하려고 했습니다" + std::string(UpperName));
		return;
	}

	std::shared_ptr<UEngineAnimation> NewAnimation = std::make_shared<UEngineAnimation>();
	NewAnimation->Sprite = FindSprite.get();
	NewAnimation->FrameIndices = _FrameIndices;
	NewAnimation->FrameIntervals = _FrameIntervals;
	NewAnimation->IsLoop = _IsLoop;
	NewAnimation->FrameEvents.resize(_FrameIndices.size(), UEngineDelegate());
	NewAnimation->SetName(UpperName);

	NewAnimation->Reset();

	UResourceManager::AddResource<UEngineAnimation>(NewAnimation, UpperName, "");
}
