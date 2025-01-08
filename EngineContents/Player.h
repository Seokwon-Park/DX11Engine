#pragma once
#include <EngineCore/Pawn.h>
#include <EngineCore/Components/InputComponent.h>
#include <EngineCore/Components/AnimatorComponent.h>
#include <EngineCore/Components/SpriteRendererComponent.h>
#include <EngineCore/Components/RigidBody2DComponent.h>

// ���� :
class APlayer : public APawn
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	void Move(FVector4 _Dir);
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<UInputComponent> Input;
	std::shared_ptr<UAnimatorComponent> Animator;
	std::shared_ptr<USpriteRendererComponent> SpriteRenderer;
	std::shared_ptr<RigidBody2DComponent> RigidBody;
};

