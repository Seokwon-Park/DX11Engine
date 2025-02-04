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

	if (false == UResourceManager::IsExist<UEngineAnimation>(UpperName))
	{
		MSGASSERT("존재하지 않는 애니메이션 이름입니다.");
		return;
	}

	std::shared_ptr<UEngineAnimation> TargetAnimation = UResourceManager::Find<UEngineAnimation>(UpperName);

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame이 애니메이션의 최대 프레임 수를 초과합니다.");
		return;
	}

	TargetAnimation->FrameEvents[_Frame] += _Function;
}

void UAnimatorComponent::SetAnimationEndEvent(std::string_view _AnimationName, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == UResourceManager::IsExist<UEngineAnimation>(UpperName))
	{
		MSGASSERT("존재하지 않는 애니메이션 이름입니다.");
		return;
	}

	SetAnimationEvent(_AnimationName, UResourceManager::Find<UEngineAnimation>(UpperName)->LastFrame(), _Function);
}

 void UAnimatorComponent::RemoveAnimationEvent(std::string_view _AnimationName, int _Frame)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == UResourceManager::IsExist<UEngineAnimation>(UpperName))
	{
		MSGASSERT("존재하지 않는 애니메이션 이름입니다.");
		return;
	}

	std::shared_ptr<UEngineAnimation> TargetAnimation = UResourceManager::Find<UEngineAnimation>(UpperName);

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame이 애니메이션의 최대 프레임 수를 초과합니다.");
		return;
	}

	TargetAnimation->FrameEvents[_Frame].Clear();
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

void UAnimatorComponent::FrameEventCheck(Uint32 _AnimationIndex)
{
	if (false == Animation->FrameEvents[_AnimationIndex].IsEmpty())
	{
		Animation->FrameEvents[_AnimationIndex]();
	}
}
