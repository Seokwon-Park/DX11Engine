#include "EnginePCH.h"
#include "TilemapColliderComponent.h"
#include <queue>


UTilemapColliderComponent::UTilemapColliderComponent()
{
}

UTilemapColliderComponent::~UTilemapColliderComponent()
{
}

void UTilemapColliderComponent::DebugRender(UCameraComponent* _Camera, float _DeltaTime)
{

}

void UTilemapColliderComponent::BeginPlay()
{
	UCollider2DComponent::BeginPlay();

	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);

	dynamicBox = b2MakeBox(TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f, TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f);

	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index = FTileIndex();
		Index.Key = TilePair.first;

		//ShapeDef = b2DefaultShapeDef();
		//ShapeDef.density = 0.5f;
		//ShapeDef.friction = 1.0f;
		//�� ���̾�
		//shapeDef.filter.categoryBits = Layer;
		//���� �浹�ϸ� �ε����� �Ǵ� �ֵ� ��Ʈ����ŷ
		//shapeDef.filter.maskBits = Layer;

		if (Visit[Index.Key] == false)
		{
			TileBFS(Index);

			std::vector<b2Vec2> points;

			for (FEdge Edge : SortedEdges)
			{
				points.push_back(Edge.A);
			}
			points.push_back(SortedEdges[0].A);
			points.push_back(SortedEdges[0].B);
			points.push_back(SortedEdges[1].B);

			b2ChainDef Def = b2DefaultChainDef();

			b2ChainDef chainDef = b2DefaultChainDef();
			chainDef.points = points.data();
			chainDef.count = points.size();

			b2ChainId myChainId = b2CreateChain(BodyId, &chainDef);
			ChainIds.push_back(myChainId);
		}
	}




	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
}


struct FloatComparator {
	bool operator()(const std::pair<float, float>& lhs, const std::pair<float, float>& rhs) const {
		float epsilon = 1e-5; // ��� ����
		if (fabs(lhs.first - rhs.first) > epsilon)
			return lhs.first < rhs.first;
		return lhs.second < rhs.second;
	}
};

struct FloatEqual {
	bool operator()(const std::pair<float, float>& lhs, const std::pair<float, float>& rhs) const {
		float epsilon = 1e-5; // ��� ����
		return fabs(lhs.first - rhs.first) < epsilon && fabs(lhs.second - rhs.second) < epsilon;
	}
};

void UTilemapColliderComponent::TileBFS(FTileIndex _Index)
{
	std::map<std::pair<float, float>, FEdge> EdgeMap;
	std::vector<FEdge> Edges;

	int X = _Index.X;
	int Y = _Index.Y;
	std::queue<std::pair<int, int>> Queue;
	Queue.push({ X,Y });
	Visit[_Index.Key] = true;
	while (false == Queue.empty())
	{
		auto [cx, cy] = Queue.front();
		Queue.pop();
		for (int i = 0; i < 4; i++)
		{
			int tx = cx + dx[i];
			int ty = cy + dy[i];
			FTileIndex tindex = { tx, ty };
			__int64 tkey = tindex.Key;
			if (TilemapComponent->Tiles.contains(tkey))//���� �� �ֺ��� Ÿ�� �� �ִµ�
			{
				if (Visit[tkey] == false) // ���� Ž������ Ÿ���̸�
				{
					Queue.push({ tx,ty });
					Visit[tkey] = true;
				}
				else // �̹� Ž���� Ÿ���̸� �� �Ұž���.
				{

				}
			}
			else // i��� ���⿡ Ÿ���� ������ ����ġ�� �������� i������ ���� �ݽð�� Edge�� �����Ѵ�.
			{
				FVector4 ConvertPos;
				ConvertPos.X = cx * TilemapComponent->ImageSize.X + TilemapComponent->ImageSize.X / 2.0f;
				ConvertPos.Y = cy * TilemapComponent->ImageSize.Y + TilemapComponent->ImageSize.Y / 2.0f;

				b2Transform Trans({ ConvertPos.X / FMath::BOX2DSCALE, ConvertPos.Y / FMath::BOX2DSCALE }, { 1.0f, 0.0f });// cos 0, sin 0
				b2Vec2 P1 = dynamicBox.vertices[i];
				b2Vec2 P2 = dynamicBox.vertices[(i + 1) % 4];
				P1 = b2TransformPoint(Trans, P1);
				P2 = b2TransformPoint(Trans, P2);
				FEdge Edge = FEdge(P1, P2);
				Edges.push_back(Edge);
				EdgeMap[{Edge.A.x, Edge.A.y}] = Edge;
			}
		}
	}
	SortedEdges.push_back(Edges[0]);
	while (SortedEdges.size() < Edges.size())
	{
		b2Vec2 Key = SortedEdges.rbegin()->B;
		SortedEdges.push_back(EdgeMap[{Key.x, Key.y}]);
	}

}

