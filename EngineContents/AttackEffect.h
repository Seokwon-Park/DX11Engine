#pragma once
#include <EngineCore/Actor.h>

#include <EngineCore/Components/AnimatorComponent.h>
#include <EngineCore/Components/SpriteRendererComponent.h>

// Ό³Έν :
class AAttackEffect : public AActor
{
public:
	// constrcuter destructer 
	AAttackEffect();
	~AAttackEffect();

	// delete Function
	AAttackEffect(const AAttackEffect& _Other) = delete;
	AAttackEffect(AAttackEffect&& _Other) noexcept = delete;
	AAttackEffect& operator=(const AAttackEffect& _Other) = delete;
	AAttackEffect& operator=(AAttackEffect&& _Other) noexcept = delete;

	void SetupEffect(std::string_view _AnimationName);

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::string AnimationName;
	std::shared_ptr<UAnimatorComponent> Animator;
	std::shared_ptr<USpriteRendererComponent> SpriteRenderer;
};

