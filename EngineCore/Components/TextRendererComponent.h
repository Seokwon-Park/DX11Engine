#pragma once
#include "Renderer2DComponent.h"
#include <EngineCore/Resources/EngineFont.h>

// Ό³Έν :
class UTextRendererComponent : public URenderer2DComponent
{
public:
	// constrcuter destructer
	UTextRendererComponent();
	~UTextRendererComponent();

	// delete Function
	UTextRendererComponent(const UTextRendererComponent& _Other) = delete;
	UTextRendererComponent(UTextRendererComponent&& _Other) noexcept = delete;
	UTextRendererComponent& operator=(const UTextRendererComponent& _Other) = delete;
	UTextRendererComponent& operator=(UTextRendererComponent&& _Other) noexcept = delete;

	void SetFont(std::string_view _FontName);
	

	virtual void TickComponent(float _DeltaTime) override;
	virtual void BeginPlay()override;
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime);
protected:

private:
	std::shared_ptr<UEngineFont> Font;
};

