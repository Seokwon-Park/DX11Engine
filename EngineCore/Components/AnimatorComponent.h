#pragma once
#include "SceneComponent.h"
#include <Resources/EngineAnimation.h>

class UAnimatorComponent :public USceneComponent
{
public:
	friend class USpriteRendererComponent;
	// Constrcuter Destructer
	UAnimatorComponent();
	~UAnimatorComponent();

	// Delete Function
	UAnimatorComponent(const UAnimatorComponent& _Other) = delete;
	UAnimatorComponent(UAnimatorComponent&& _Other) noexcept = delete;
	UAnimatorComponent& operator=(const UAnimatorComponent& _Other) = delete;
	UAnimatorComponent& operator=(UAnimatorComponent&& _Other) noexcept = delete;

	inline void CancelAnimation() { CurAnimation = nullptr; }
	// ��������Ʈ�� �ε��� ������ ������� �ִϸ��̼��� ����
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		int _FrameStart, int _FrameEnd, float _FrameInterval = 0.1f, bool _IsLoop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _Indices, float _FrameIntervals, bool _IsLoop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _FrameIndex, std::vector<float> _FrameInterval, bool _IsLoop = true);

	void ChangeAnimation(std::string_view _AnimationName, bool _IsForce = false);
	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);
protected:

private:
	UEngineAnimation* CurAnimation;
	std::map<std::string, UEngineAnimation> Animations;
};

