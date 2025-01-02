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

