#pragma once
#include <EngineCore/Pawn.h>

#include <EngineCore/Components/AnimatorComponent.h>
#include <EngineCore/Components/SpriteRendererComponent.h>
#include <EngineCore/Components/Rigidbody2DComponent.h>
#include <EngineCore/Components/BoxCollider2DComponent.h>
#include <EngineCore/Components/CapsuleCollider2DComponent.h>

// Ό³Έν :
class AEntity : public APawn
{
public:
	// constrcuter destructer
	AEntity();
	~AEntity();

	// delete Function
	AEntity(const AEntity& _Other) = delete;
	AEntity(AEntity&& _Other) noexcept = delete;
	AEntity& operator=(const AEntity& _Other) = delete;
	AEntity& operator=(AEntity&& _Other) noexcept = delete;

	inline UAnimatorComponent* GetAnimatorComponent() { return Animator.get(); }
	inline USpriteRendererComponent* GetSpriteRendererComponent() { return SpriteRenderer.get(); }
	inline URigidbody2DComponent* GetRigidbody2DComponent() { return RigidBody2D.get(); }
	inline UBoxCollider2DComponent* GetBoxCollider2DComponent() { return BoxCollider2D.get(); }
	inline UCapsuleCollider2DComponent* GetCapsuleCollider2DComponent() { return CapsuleCollider2D.get(); }

	void Flip();
	void SetVelocity(FVector2 _Velocity);

	bool IsGroundDetected();

	virtual void Tick(float _DeltaTime) override;
	int FacingDir = -1;
protected:
	virtual void BeginPlay() override;

	std::shared_ptr<UAnimatorComponent> Animator;
	std::shared_ptr<USpriteRendererComponent> SpriteRenderer;
	std::shared_ptr<URigidbody2DComponent> RigidBody2D;
	std::shared_ptr<UBoxCollider2DComponent> BoxCollider2D;
	std::shared_ptr<UCapsuleCollider2DComponent> CapsuleCollider2D;
private:
};

