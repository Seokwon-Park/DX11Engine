#pragma once
#include <EngineCore/RenderUnit.h>
#include <EngineCore/Components/Renderer2DComponent.h>

// Ό³Έν :
class UGridRendererComponent : public URenderer2DComponent
{
public:
	// constrcuter destructer
	ENGINE_API UGridRendererComponent();
	ENGINE_API ~UGridRendererComponent();

	// delete Function
	UGridRendererComponent(const UGridRendererComponent& _Other) = delete;
	UGridRendererComponent(UGridRendererComponent&& _Other) noexcept = delete;
	UGridRendererComponent& operator=(const UGridRendererComponent& _Other) = delete;
	UGridRendererComponent& operator=(UGridRendererComponent&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime) override;
	virtual void TickComponent(float _DeltaTime)override;

private:
	std::shared_ptr<URenderUnit> GridRenderUnit;


};

