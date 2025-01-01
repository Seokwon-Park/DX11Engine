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
		MSGASSERT(std::string(_AnimationName) + "�߸��� ���� ����. FrameStart�� FrameEnd���� Ů�ϴ�.");
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
		MSGASSERT("�� �迭 ������ ũ�Ⱑ �ٸ��ϴ�. _Index�� _Interval�� ũ�Ⱑ �����ؾ� �մϴ�.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UResourceManager::Find<UEngineSprite>(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� �ִϸ��̼� ������ ����Ϸ��� �߽��ϴ�" + std::string(UpperName));
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

	//if (false == Animations.contains(UpperName))
	//{
	//	MSGASSERT("�������� �ʴ� �ִϸ��̼� �̸��Դϴ�.");
	//	return;
	//}

	//UEngineAnimation* TargetAnimation = &Animations[UpperName];

	/*if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame�� �ִϸ��̼��� �ִ� ������ ���� �ʰ��մϴ�.");
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

void UAnimatorComponent::FrameEventCheck(uint32 _AnimationIndex)
{
	if (false == Animation->FrameEvents[_AnimationIndex].IsEmpty())
	{
		Animation->FrameEvents[_AnimationIndex]();
	}
}
