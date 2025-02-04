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
		MSGASSERT("�������� ���� �ִϸ��̼����� �����Ϸ��� �߽��ϴ�. = " + UpperName);
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
		MSGASSERT("�������� �ʴ� �ִϸ��̼� �̸��Դϴ�.");
		return;
	}

	std::shared_ptr<UEngineAnimation> TargetAnimation = UResourceManager::Find<UEngineAnimation>(UpperName);

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame�� �ִϸ��̼��� �ִ� ������ ���� �ʰ��մϴ�.");
		return;
	}

	TargetAnimation->FrameEvents[_Frame] += _Function;
}

void UAnimatorComponent::SetAnimationEndEvent(std::string_view _AnimationName, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == UResourceManager::IsExist<UEngineAnimation>(UpperName))
	{
		MSGASSERT("�������� �ʴ� �ִϸ��̼� �̸��Դϴ�.");
		return;
	}

	SetAnimationEvent(_AnimationName, UResourceManager::Find<UEngineAnimation>(UpperName)->LastFrame(), _Function);
}

 void UAnimatorComponent::RemoveAnimationEvent(std::string_view _AnimationName, int _Frame)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == UResourceManager::IsExist<UEngineAnimation>(UpperName))
	{
		MSGASSERT("�������� �ʴ� �ִϸ��̼� �̸��Դϴ�.");
		return;
	}

	std::shared_ptr<UEngineAnimation> TargetAnimation = UResourceManager::Find<UEngineAnimation>(UpperName);

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame�� �ִϸ��̼��� �ִ� ������ ���� �ʰ��մϴ�.");
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
	// �ִϸ��̼� �����Ű�� �ڵ带 ComponentTick���� �Ű��. 
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
