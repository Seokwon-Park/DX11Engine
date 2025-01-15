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

	UpdateCollider();

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::UpdateCollider()
{
	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tilemap->GetTilemapData())
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
			SortedEdges.clear();
			TileBFS(Index);

			std::vector<b2Vec2> points;

			for (FEdge Edge : SortedEdges)
			{

				points.push_back(IndexToRealScaleMap[Edge.A]);
			}
			points.push_back(IndexToRealScaleMap[SortedEdges[0].A]);
			points.push_back(IndexToRealScaleMap[SortedEdges[0].B]);

			b2ChainDef Def = b2DefaultChainDef();

			b2ChainDef chainDef = b2DefaultChainDef();
			chainDef.points = points.data();
			chainDef.count = points.size();
			chainDef.friction = 0.0f;

			b2ChainId myChainId = b2CreateChain(BodyId, &chainDef);
			ChainIds.push_back(myChainId);
		}
	}
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
}



void UTilemapColliderComponent::TileBFS(FTileIndex _Index)
{
	std::map<std::pair<int, int>, FEdge> EdgeMap;
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
			if (TilemapComponent->Tilemap->Contains(tindex))//���� �� �ֺ��� Ÿ�� �� �ִµ�
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

				std::pair<int, int> Point1;
				std::pair<int, int> Point2;
				if (i == 0)
				{
					Point1 = { cx*2 - 1,cy*2 - 1 };
					Point2 = { cx*2 + 1,cy*2 - 1 };
				}
				else if (i == 1)
				{
					Point1 = { cx*2 + 1,cy*2 - 1 };
					Point2 = { cx*2 + 1,cy*2 + 1 };
				}
				else if (i == 2)
				{
					Point1 = { cx*2 + 1,cy*2 + 1 };
					Point2 = { cx*2 - 1,cy*2 + 1 };
				}
				else
				{
					Point1 = { cx*2 - 1,cy*2 + 1 };
					Point2 = { cx*2 - 1,cy*2 - 1 };
				}

				b2Transform Trans({ ConvertPos.X / FMath::BOX2DSCALE, ConvertPos.Y / FMath::BOX2DSCALE }, { 1.0f, 0.0f });// cos 0, sin 0
				b2Vec2 P1 = dynamicBox.vertices[i];
				b2Vec2 P2 = dynamicBox.vertices[(i + 1) % 4];
				P1 = b2TransformPoint(Trans, P1);
				P2 = b2TransformPoint(Trans, P2);
				IndexToRealScaleMap[Point1] = P1;
				IndexToRealScaleMap[Point2] = P2;
				FEdge Edge = { Point1, Point2 };
				Edges.push_back(Edge);
				EdgeMap[Edge.A] = Edge;
			}
		}
	}
	SortedEdges.push_back(Edges[0]);
	while (SortedEdges.size() < Edges.size())
	{
		std::pair<int, int> Key = SortedEdges.rbegin()->B;
		//if (EdgeMap.contains(Key) == false)
		//{
		//	return;
		//}
		SortedEdges.push_back(EdgeMap[Key]);
	}

}

