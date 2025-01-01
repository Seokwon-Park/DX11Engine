#include "EnginePCH.h"
#include "AnimatorComponent.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>

UAnimatorComponent::UAnimatorComponent()
{
}

UAnimatorComponent::~UAnimatorComponent()
{
}



void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
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

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _Indices, float _FrameInterval, bool _IsLoop)
{
	std::vector<float> Intervals(_Indices.size(), _FrameInterval);

	CreateAnimation(_AnimationName, _SpriteName, _Indices, Intervals, _IsLoop);
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
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
	
	NewAnimation->Reset();

	UResourceManager::AddResource<UEngineAnimation>(NewAnimation, UpperName, "NoPath");
}

void UAnimatorComponent::SetAnimation(std::string_view _AnimationName, bool _IsForce /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	std::shared_ptr<UEngineAnimation> Result = UResourceManager::Find<UEngineAnimation>(UpperName);

	if (Result == nullptr)
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	Animation = Result.get();
	Animation->Reset();

	if (false == Animation->FrameEvents[0].IsEmpty())
	{
		Animation->FrameEvents[0]();
	}

	//Auto Scale;
}

void UAnimatorComponent::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	//if (false == Animations.contains(UpperName))
	//{
	//	MSGASSERT("존재하지 않는 애니메이션 이름입니다.");
	//	return;
	//}

	//UEngineAnimation* TargetAnimation = &Animations[UpperName];

	/*if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame이 애니메이션의 최대 프레임 수를 초과합니다.");
		return;
	}*/

	//TargetAnimation->Events[_Frame] += _Function;
}

void UAnimatorComponent::BeginPlay()
{
}

void UAnimatorComponent::TickComponent(float _DeltaTime)
{
	UActorComponent::TickComponent(_DeltaTime);
	// 애니메이션 진행시키는 코드를 ComponentTick으로 옮겼다. 
	if (SpriteRenderer == nullptr) return;
	if (nullptr != Animation)
	{
		std::vector<int>& Indices = Animation->FrameIndices;
		std::vector<float>& Intervals = Animation->FrameIntervals;

		FrameTimer += _DeltaTime;

		float TimeToNextFrame = Intervals[Animation->CurIndex];

		if (FrameTimer > TimeToNextFrame)
		{
			FrameTimer = 0.0f;
			Animation->CurIndex += 1;

			if (Animation->CurIndex >= Indices.size())
			{
				if (true == Animation->IsLoop)
				{
					Animation->CurIndex = 0;

					FrameEventCheck(Animation->CurIndex);
				}
				else
				{
					--Animation->CurIndex;
				}
			}
			else
			{
				FrameEventCheck(Animation->CurIndex);
			}

		}
		SpriteRenderer->SetSprite(Animation->Sprite, Indices[Animation->CurIndex]);

		//CurIndex = Indices[Animation->CurIndex];
		// ++Animation->CurIndex;
	}
}

void UAnimatorComponent::FrameEventCheck(uint32 _AnimationIndex)
{
	if (false == Animation->FrameEvents[_AnimationIndex].IsEmpty())
	{
		Animation->FrameEvents[_AnimationIndex]();
	}
}
