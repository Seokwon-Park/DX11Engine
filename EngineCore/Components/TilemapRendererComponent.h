#pragma once
#include "RendererComponent.h"
#include "TilemapComponent.h"
#include <EngineCore/Enums/EngineLayer.h>

// Ό³Έν :
class UTilemapRendererComponent : public URendererComponent
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

	ENGINE_API void SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer = 0);
	ENGINE_API inline std::pair<int, int> GetOrder() { return std::make_pair(static_cast<int>(SortingLayer), OrderInLayer); }

	ENGINE_API void SetTilemap(std::shared_ptr<UTilemapComponent> _TilemapComponent) { SetTilemap(_TilemapComponent.get()); }
	ENGINE_API void SetTilemap(UTilemapComponent* _TilemapComponent) { TilemapComponent = _TilemapComponent; }

	FVector4 TileIndexToWorldPos(FTileIndex _Pos);
protected:
	ENGINE_API void Render(class UCameraComponent* _Camera, float _DeltaTime) override;
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;

private:
	ESortingLayer SortingLayer = ESortingLayer::Default;
	int OrderInLayer = 0;

	std::shared_ptr<URenderUnit> Unit;
	
	class UTilemapComponent* TilemapComponent = nullptr;

};
