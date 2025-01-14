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
	// 각 타일의 인덱스에 대해 월드 좌표로 변환- >static body로 충돌체를 생성한다

	std::map<std::vector<float>, int> Edges;

	std::vector<std::vector<float>> keys;

	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;
		Index.Key = TilePair.first;

		dynamicBox = b2MakeBox(TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f, TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f);
		//ShapeDef = b2DefaultShapeDef();
		//ShapeDef.density = 0.5f;
		//ShapeDef.friction = 1.0f;
		//내 레이어
		//shapeDef.filter.categoryBits = Layer;
		//내가 충돌하면 부딪혀야 되는 애들 비트마스킹
		//shapeDef.filter.maskBits = Layer;

		if (Visit[Index.Key] == false)
		{
			TileDFS(Index);
		}

		//FVector4 ConvertPos;
		//ConvertPos.X = Index.X * TilemapComponent->ImageSize.X + TilemapComponent->ImageSize.X / 2.0f;
		//ConvertPos.Y = Index.Y * TilemapComponent->ImageSize.Y + TilemapComponent->ImageSize.Y / 2.0f;

		//b2BodyDef BodyDef = b2DefaultBodyDef();
		//BodyDef.type = b2_staticBody;
		//BodyDef.position = { ConvertPos.X / FMath::BOX2DSCALE,ConvertPos.Y / FMath::BOX2DSCALE };
		////BodyDef.rotation = b2MakeRot(FMath::DegreeToRadian(10.0f));
		////Parent->GetTransformRef().Rotation = FVector4(0.0f, 0.0f, FMath::DegreeToRadian(10.0f), 1.0f);
		////Parent->UpdateTransform();
		////BodyDef.fixedRotation = true;
		//b2BodyId NewBodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		//b2CreatePolygonShape(NewBodyId, &ShapeDef, &dynamicBox);
		//BodyIds.push_back(NewBodyId);

	}

	for (auto K : keys)
	{
		Edges.erase(K);
	}

	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////
	b2BodyDef D = b2DefaultBodyDef();
	b2BodyId TestBodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &D);
	//b2ChainSegment chainSegment = { 0 };
	//chainSegment.ghost1 = b2Vec2(1.7f, 0.0f);
	//chainSegment.segment = b2Segment({ 1.0f, 0.25f }, { 0.0f, 0.0f });
	//chainSegment.ghost2 = b2Vec2(-1.7f, 0.4f);

	std::vector<b2Vec2> points;

	for (FEdge Edge : Result)
	{
		points.push_back(Edge.A);
	}
	points.push_back(Result.begin()->A);

	b2ChainDef Def = b2DefaultChainDef();


	b2ChainDef chainDef = b2DefaultChainDef();
	chainDef.points = points.data();
	chainDef.count = points.size();

	b2ChainId myChainId = b2CreateChain(TestBodyId, &chainDef);

	std::vector<b2Vec2> points2 = {
		{1.7f, 0.0f},
		{10.0f, 2.0f},
		{-10.0f, 0.0f},
		{-1.7f, 0.4f}
	};

	b2ChainDef chainDef2 = b2DefaultChainDef();
	chainDef.points = points2.data();
	chainDef.count = points2.size();

	b2ChainId myChainId2 = b2CreateChain(TestBodyId, &chainDef);


	//b2CreateChain(TestBodyId, &Def);
	///////////////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////
	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
}

void UTilemapColliderComponent::TileDFS(FTileIndex _Index)
{
	int cx = _Index.X;
	int cy = _Index.Y;
	Visit[_Index.Key] = true;
	for (int i = 0; i < 4; i++)
	{
		int tx = cx + dx[i];
		int ty = cy + dy[i];
		FTileIndex tindex = { tx, ty };
		__int64 tkey = tindex.Key;
		if (TilemapComponent->Tiles.contains(tkey))//만약 내 주변에 타일 이 있는데
		{
			if (Visit[tkey] == false) // 아직 탐색안한 타일이면
			{
				TileDFS(tindex);
			}
			else // 이미 탐색한 타일이면 뭐 할거없음.
			{

			}
		}
		else // i라는 방향에 타일이 없으면 내위치를 기준으로 i방향을 향해 반시계로 Edge를 생성한다.
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
			if (Result.empty())
			{
				Result.push_back(Edge);
			}
			else
			{
				auto itr = Result.begin();
				while (itr != Result.end() && (*itr).B != Edge.A) itr++;
				if (itr == Result.end())
				{
					Result.push_back(Edge);
				}
				else
				{
					itr++;
					Result.insert(itr, Edge);
				}
			}
		}
	}
}

