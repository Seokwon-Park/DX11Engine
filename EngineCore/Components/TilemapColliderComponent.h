#pragma once
#include "TilemapComponent.h"
#include "Collider2DComponent.h"

struct FEdge
{
	std::pair<int,int> A;
	std::pair<int,int> B;
};


// Ŭ���� ���� :
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
	void UpdateCollider();
	void TickComponent(float _DeltaTime) override;
private:
	// BFS
	std::map<std::pair<int, int>, b2Vec2> IndexToRealScaleMap;
	void TileBFS(FTileIndex _Index);
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	std::unordered_map<__int64, bool> Visit;
	//////////////////////////////////////////////////

	ECollisionLayer Layer;
	std::vector<FEdge> SortedEdges;


	b2Polygon dynamicBox;
	std::vector<b2ChainId> ChainIds;

	class UTilemapComponent* TilemapComponent = nullptr;
};
