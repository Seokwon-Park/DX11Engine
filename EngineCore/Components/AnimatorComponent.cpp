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
	int _FrameStart, int _FrameEnd, float _FrameInterval, bool _IsLoop)
{
	if (_FrameStart > _FrameEnd)
	{
		MSGASSERT(std::string(_AnimationName) + "�߸��� ���� ����. FrameStart�� FrameEnd���� Ů�ϴ�.");
		return;
	}

	int Size = (_FrameEnd - _FrameStart) + 1;

	std::vector<int> Indices;
	std::vector<float> Intervals(Size, _FrameInterval);

	for (int i = 0; i < Size; i++)
	{
		Indices.push_back(_FrameStart + i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Indices, Intervals, _IsLoop);
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _Indices, float _FrameIntervals, bool _IsLoop)
{
	std::vector<float> Intervals(_Indices.size(), _FrameIntervals);


	CreateAnimation(_AnimationName, _SpriteName, _Indices, Intervals, _IsLoop);
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _FrameIndex, std::vector<float> _FrameInterval, bool _IsLoop)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_FrameIndex.size() != _FrameInterval.size())
	{
		MSGASSERT("�� �迭 ������ ũ�Ⱑ �ٸ��ϴ�. _Index�� _Interval�� ũ�Ⱑ �����ؾ� �մϴ�.");
		return;
	}

	if (Animations.contains(UpperName))
	{
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UResourceManager::Find<UEngineSprite>(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� �ִϸ��̼� ������ ����Ϸ��� �߽��ϴ�" + std::string(UpperName));
		return;
	}

	UEngineAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite.get();
	NewAnimation.FrameIndices = _FrameIndex;
	NewAnimation.FrameIntervals = _FrameInterval;
	NewAnimation.IsLoop = _IsLoop;
	NewAnimation.Reset();

	Animations.insert(std::make_pair(UpperName, NewAnimation));
}

void UAnimatorComponent::ChangeAnimation(std::string_view _AnimationName, bool _IsForce /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MSGASSERT("�������� ���� �ִϸ��̼����� �����Ϸ��� �߽��ϴ�. = " + UpperName);
		return;
	}

	UEngineAnimation* TargetAnimation = &Animations[UpperName];

	// ���� �ִϸ��̼����� ��ü�ϴ� �� or ���� ��ü�� false�� ��??
	// �߸𸣰ڴ� �̺κ� ����.
	if (CurAnimation == TargetAnimation && false == _IsForce)
	{
		return;
	}

	CurAnimation = &Animations[UpperName];
	CurAnimation->Reset();
}

void UAnimatorComponent::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MSGASSERT("�������� �ʴ� �ִϸ��̼� �̸��Դϴ�.");
		return;
	}

	UEngineAnimation* TargetAnimation = &Animations[UpperName];

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame�� �ִϸ��̼��� �ִ� ������ ���� �ʰ��մϴ�.");
		return;
	}

	//TargetAnimation->Events[_Frame] += _Function;
}