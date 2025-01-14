#pragma once
#include "TilemapComponent.h"
#include "Collider2DComponent.h"

struct FEdge
{
	b2Vec2 A;
	b2Vec2 B;
};


// 클래스 설명 :
class UTilemapColliderComponent : public UCollider2DComponent
{
public:
	// Constrcuter Destructer
	ENGINE_API UTilemapColliderComponent();
	ENGINE_API ~UTilemapColliderComponent();

	// Delete Function
	UTilemapColliderComponent(const UTilemapColliderComponent& _Other) = delete;
	UTilemapColliderComponent(UTilemapColliderComponent&& _Other) noexcept = delete;
	UTilemapColliderComponent& operator=(const UTilemapColliderComponent& _Other) = delete;
	UTilemapColliderComponent& operator=(UTilemapColliderComponent&& _Other) noexcept = delete;

	ENGINE_API void SetTilemap(std::shared_ptr<UTilemapComponent> _TilemapComponent) { SetTilemap(_TilemapComponent.get()); }
	ENGINE_API void SetTilemap(UTilemapComponent* _TilemapComponent) { TilemapComponent = _TilemapComponent; }

	ENGINE_API virtual void DebugRender(class UCameraComponent* _Camera, float _DeltaTime)override;
protected:
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;
private:

	void TileDFS(FTileIndex _Index);
	std::unordered_map<__int64, bool> Visit;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	ECollisionLayer Layer;

	std::list<FEdge> Result;

	b2Polygon dynamicBox;
	std::vector<b2BodyId> BodyIds;

	class UTilemapComponent* TilemapComponent = nullptr;
};
