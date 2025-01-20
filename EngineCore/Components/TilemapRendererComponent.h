#pragma once
#include "Renderer2DComponent.h"
#include "TilemapComponent.h"
#include <EngineCore/Enums/EngineLayer.h>
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

// Ό³Έν :
class UTilemapRendererComponent : public URenderer2DComponent
{
public:
	// constrcuter destructer
	ENGINE_API UTilemapRendererComponent();
	ENGINE_API ~UTilemapRendererComponent();

	// delete Function
	UTilemapRendererComponent(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent(UTilemapRendererComponent&& _Other) noexcept = delete;
	UTilemapRendererComponent& operator=(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent& operator=(UTilemapRendererComponent&& _Other) noexcept = delete;

	ENGINE_API virtual void SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer = 0) override;

	ENGINE_API void SetTilemap(std::shared_ptr<UTilemapComponent> _TilemapComponent) { SetTilemap(_TilemapComponent.get()); }
	ENGINE_API void SetTilemap(UTilemapComponent* _TilemapComponent) { TilemapComponent = _TilemapComponent; }

protected:
	ENGINE_API void Render(class UCameraComponent* _Camera, float _DeltaTime) override;
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;

private:
	std::shared_ptr<class UEngineSprite> Sprite;
	std::shared_ptr<URenderUnit> Unit;
	
	class UTilemapComponent* TilemapComponent = nullptr;
};
