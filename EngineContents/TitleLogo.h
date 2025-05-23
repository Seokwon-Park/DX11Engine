#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Components/SpriteRendererComponent.h>
#include <EngineCore/Components/BoxCollider2DComponent.h>


// ���� :
class ATitleLogo : public AActor
{
public:
	// constrcuter destructer
	ATitleLogo();
	~ATitleLogo();

	// delete Function
	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<USpriteRendererComponent> SpriteRenderer;
	std::shared_ptr<UBoxCollider2DComponent> Collider;

};

