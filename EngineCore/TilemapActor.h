#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Components/TilemapComponent.h>
#include <EngineCore/Components/TilemapRendererComponent.h>
#include <EngineCore/Components/TilemapColliderComponent.h>

// Ό³Έν :
class ATilemapActor : public AActor
{
public:
	// constrcuter destructer
	ENGINE_API ATilemapActor();
	ENGINE_API ~ATilemapActor();

	// delete Function
	ATilemapActor(const ATilemapActor& _Other) = delete;
	ATilemapActor(ATilemapActor&& _Other) noexcept = delete;
	ATilemapActor& operator=(const ATilemapActor& _Other) = delete;
	ATilemapActor& operator=(ATilemapActor&& _Other) noexcept = delete;

	ENGINE_API void PlaySetup(std::string_view _TilemapName);
	ENGINE_API void EditSetup(std::string _SpriteName, FVector2 _TileSize, FVector2 _TilePivot);
		


	ENGINE_API inline UTilemapComponent* GetTilmapComponent() { return TilemapComponent.get(); }
	ENGINE_API inline UTilemapRendererComponent* GetTilemapRendererComponent() { return TilemapRendererComponent.get(); }
	ENGINE_API inline UTilemapColliderComponent* GetTilemapColliderComponent() { return TilemapColliderComponent.get(); }

	ENGINE_API virtual void Tick(float _DeltaTime) override;
protected:
	ENGINE_API virtual void BeginPlay() override;

	std::shared_ptr<UTilemapComponent> TilemapComponent;
	std::shared_ptr<UTilemapRendererComponent> TilemapRendererComponent;
	std::shared_ptr<UTilemapColliderComponent> TilemapColliderComponent;

private:
};

