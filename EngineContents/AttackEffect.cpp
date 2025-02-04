#include "EnginePCH.h"
#include "AttackEffect.h"

AAttackEffect::AAttackEffect()
{
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();

	Animator = CreateDefaultSubobject<UAnimatorComponent>();
	Animator->SetSpriteRenderer(SpriteRenderer);

	SpriteRenderer->SetupAttachment(RootComponent);
}

AAttackEffect::~AAttackEffect()
{
	Animator->RemoveAnimationEvent(AnimationName, UResourceManager::Find<UEngineAnimation>(AnimationName)->LastFrame());
}

void AAttackEffect::BeginPlay()
{
	AActor::BeginPlay();
	Animator->SetAnimationEndEvent(AnimationName, std::bind(&AAttackEffect::Destroy, this));
}

void AAttackEffect::SetupEffect(std::string_view _AnimationName)
{
	AnimationName = _AnimationName;
	Animator->SetAnimation(_AnimationName);
}

void AAttackEffect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
