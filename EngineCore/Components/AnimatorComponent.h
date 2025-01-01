#pragma once
#include "SceneComponent.h"
#include "SpriteRendererComponent.h"
#include <EngineCore/Resources/EngineAnimation.h>

class UAnimatorComponent :public UActorComponent
{
public:
	// Constrcuter Destructer
	ENGINE_API UAnimatorComponent();
	ENGINE_API ~UAnimatorComponent();

	// Delete Function
	UAnimatorComponent(const UAnimatorComponent& _Other) = delete;
	UAnimatorComponent(UAnimatorComponent&& _Other) noexcept = delete;
	UAnimatorComponent& operator=(const UAnimatorComponent& _Other) = delete;
	UAnimatorComponent& operator=(UAnimatorComponent&& _Other) noexcept = delete;

	ENGINE_API inline void SetSpriteRenderer(USpriteRendererComponent* _SpriteRenderer) { SpriteRenderer = _SpriteRenderer; }
	ENGINE_API inline void SetSpriteRenderer(std::shared_ptr<USpriteRendererComponent> _SpriteRenderer) { SpriteRenderer = _SpriteRenderer.get(); }

	// inline void CancelAnimation() { Animation = nullptr; }
	// 스프라이트의 인덱스 범위를 기반으로 애니메이션을 생성
	ENGINE_API void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		int _StartFrame, int _EndFrame, float _FrameInterval = 0.1f, bool _IsLoop = true);
	ENGINE_API void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _Indices, float _FrameInterval, bool _IsLoop = true);
	ENGINE_API void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
		std::vector<int> _FrameIndices, std::vector<float> _FrameIntervals, bool _IsLoop = true);
	ENGINE_API void SetAnimation(std::string_view _AnimationName, bool _IsForce = false);
	ENGINE_API void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

	ENGINE_API void BeginPlay() override;
	virtual void TickComponent(float _DeltaTime)override;
	void FrameEventCheck(uint32 _AnimationIndex);
protected:

private:
	float FrameTimer = 0.0f;
	UEngineAnimation* Animation = nullptr;
	USpriteRendererComponent* SpriteRenderer = nullptr;
};

