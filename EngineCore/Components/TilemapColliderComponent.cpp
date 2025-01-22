#include "EnginePCH.h"
#include "TilemapColliderComponent.h"
#include <queue>
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

UTilemapColliderComponent::UTilemapColliderComponent()
{
}

UTilemapColliderComponent::~UTilemapColliderComponent()
{
}

void UTilemapColliderComponent::DebugRender(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	auto& Test = Parent->GetTransformRef();
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrixTranspose();
	VC.Proj = _Camera->GetProjectionMatrixTranspose();

	float Temp[4] = { 0.5f,0.5f,0.0f,0.0f };
	auto test = FColor(0.0f, 1.0f, 0.0f, 1.0f);

	for (auto RenderUnit : RenderUnits)
	{
		RenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
		RenderUnit->SetConstantBufferData("Offset", EShaderType::VS, Temp);
		RenderUnit->SetConstantBufferData("DebugColor", EShaderType::PS, test);
		RenderUnit->Render(_Camera, _DeltaTime);
	}
}



void UTilemapColliderComponent::BeginPlay()
{
	UCollider2DComponent::BeginPlay();

	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);

	UpdateCollider();

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::UpdateCollider()
{
	Visit.clear();
	RenderUnits.clear();
	std::vector<b2ChainId> DeleteList = ChainIds;
	ChainIds.clear();

	for (int i = 0; i < PolygonCount; i++)
	{
		UResourceManager::RemoveResource<UEngineVertexBuffer>("TmapCol" + std::to_string(i));
	}
	PolygonCount = 0;

	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tilemap->GetTilemapData())
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index = FTileIndex();
		Index.Key = TilePair.first;

		float HalfHeight = TilemapComponent->TileSize.X / FMath::BOX2DSCALE / 2.0f;
		float HalfWidth = TilemapComponent->TileSize.X / FMath::BOX2DSCALE / 2.0f;
		float Radian = FMath::DegreeToRadian(Tile.RotatedCount * 90.0f);
		FVector4 ConvertPos = TilemapComponent->TileIndexToWorldPos(Index);

		std::vector<FVector4> Points;
		switch (Tile.PolygonType)
		{
		case ETilePolygon::Default:
		{
			dynamicBox = b2MakeBox(HalfWidth, HalfHeight);
		}
		break;
		case ETilePolygon::Slope1:
		{
			Points = { FVector4(-HalfWidth, HalfHeight), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight) };
			break;
		}
		case ETilePolygon::Slope2:
		{
			Points = { FVector4(-HalfWidth, HalfHeight), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight) ,FVector4(HalfWidth, 0.0f) };
			break;
		}
		case ETilePolygon::Slope3:
		{
			Points = { FVector4(-HalfWidth, 0.0f), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight) };
			break;
		}
		case ETilePolygon::Slope4:
		{
			Points = { FVector4(-HalfWidth, HalfHeight), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight), FVector4(HalfWidth, HalfHeight - (2.0f * HalfHeight / 3.0f)) };
			break;
		}
		case ETilePolygon::Slope5:
		{
			Points = { FVector4(-HalfWidth, HalfHeight - (2.0f * HalfHeight / 3.0f)), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight + (2.0f * HalfHeight / 3.0f)) };
			break;
		}
		case ETilePolygon::Slope6:
		{
			Points = { FVector4(-HalfWidth, -HalfHeight + (2.0f * HalfHeight / 3.0f)), FVector4(-HalfWidth, -HalfHeight), FVector4(HalfWidth, -HalfHeight) };
			break;
		}
		default:
			break;
		}

		if (ETilePolygon::Default != Tile.PolygonType)
		{
			CreateSlope(Points, Tile);
		}
		//ShapeDef = b2DefaultShapeDef();
		//ShapeDef.density = 0.5f;
		//ShapeDef.friction = 1.0f;
		//내 레이어
		//shapeDef.filter.categoryBits = Layer;
		//내가 충돌하면 부딪혀야 되는 애들 비트마스킹
		//shapeDef.filter.maskBits = Layer;

		if (Visit[Index.Key] == false && Tile.PolygonType == ETilePolygon::Default)
		{
			int StartIx = 0;
			SortedEdges.clear();
			IndexToRealScaleMap.clear();
			TileBFS(Index);

			std::vector<b2Vec2> points;
			std::vector<Vertex> Vertices;
			std::vector<Uint32> Indices;

			points.push_back(IndexToRealScaleMap[SortedEdges[0].A]);
			points.push_back(IndexToRealScaleMap[SortedEdges[SortedEdges.size() - 1].A]);
			for (FEdge Edge : SortedEdges)
			{
				points.push_back(IndexToRealScaleMap[Edge.A]);
				Vertices.push_back(Vertex{ FVector4(IndexToRealScaleMap[Edge.A].x * FMath::BOX2DSCALE,IndexToRealScaleMap[Edge.A].y * FMath::BOX2DSCALE, 1.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} });
				Indices.push_back(StartIx);
				Indices.push_back(StartIx+1);
				StartIx++;
			}
			Indices.pop_back();
			Indices.push_back(0);

			points.push_back(IndexToRealScaleMap[SortedEdges[0].A]);
			points.push_back(IndexToRealScaleMap[SortedEdges[SortedEdges.size() - 1].A]);

			Uint32 DataSize = static_cast<Uint32>(sizeof(Vertex) * Vertices.size());
			Uint32 VertexCount = static_cast<Uint32>(Vertices.size());

			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("TmapCol"+std::to_string(PolygonCount),
				Vertices.data(), DataSize, VertexCount);

			std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create(Indices.data(), Indices.size());

			std::shared_ptr<UEngineMesh> Mesh = std::make_shared<UEngineMesh>();
			Mesh->SetVertexBuffer(VertexBuffer);
			Mesh->SetIndexBuffer(IndexBuffer);
			Mesh->SetTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
			
			auto& RenderUnit = RenderUnits.emplace_back(std::make_shared<URenderUnit>());
			RenderUnit->Init("TmapCollider", "ColliderDebug");
			RenderUnit->SetMesh(Mesh);

			b2ChainDef Def = b2DefaultChainDef();

			b2ChainDef chainDef = b2DefaultChainDef();
			chainDef.points = points.data();
			chainDef.count = static_cast<int32_t>(points.size());
			chainDef.friction = 0.0f;

			b2ChainId myChainId = b2CreateChain(BodyId, &chainDef);
			ChainIds.push_back(myChainId);

			PolygonCount++;
		}
	}

	for (auto id : DeleteList)
	{
		b2DestroyChain(id);
	}
}

void UTilemapColliderComponent::CreateSlope(std::vector<FVector4> _Points, FTileData& _Tile)
{
	FVector4 ConvertPos = TilemapComponent->TileIndexToWorldPos(_Tile.Index);

	FTransform Trans;
	Trans.Location = FVector4(ConvertPos.X / FMath::BOX2DSCALE, ConvertPos.Y / FMath::BOX2DSCALE);
	Trans.Rotation = FVector4(0.0f, 180.0f * _Tile.IsFlip, _Tile.RotatedCount * 90.0f);
	Trans.UpdateTransform();

	std::vector<b2Vec2> Vecs;
	for (int i = 0; i < _Points.size(); i++)
	{
		_Points[i] = Trans.WorldMatrix * _Points[i];
		Vecs.emplace_back(b2Vec2(_Points[i].X, _Points[i].Y));
	}


	std::vector<b2Vec2> points;

	points.push_back(Vecs[0]);
	for (int i = 0; i < _Points.size(); i++)
	{
		points.emplace_back(Vecs[i]);
	}
	points.push_back(Vecs[0]);
	points.push_back(Vecs[0]);

	if (_Tile.IsFlip)
	{
		std::reverse(points.begin(), points.end());
	}

	b2ChainDef chainDef = b2DefaultChainDef();
	chainDef.points = points.data();
	chainDef.count = static_cast<int32_t>(points.size());
	chainDef.friction = 0.0f;

	b2ChainId myChainId = b2CreateChain(BodyId, &chainDef);
	ChainIds.push_back(myChainId);
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
			FTileIndex TIndex = { tx, ty };
			__int64 Tkey = TIndex.Key;
			if (TilemapComponent->Tilemap->Contains(TIndex) &&
				TilemapComponent->GetTile(TIndex)->PolygonType == ETilePolygon::Default)//만약 내 주변에 타일 이 있는데 사각형 타일에 대해서만
			{
				if (Visit[Tkey] == false) // 아직 탐색안한 타일이면
				{
					Queue.push({ tx,ty });
					Visit[Tkey] = true;
				}
				else // 이미 탐색한 타일이면 뭐 할거없음.
				{

				}
			}
			else // i라는 방향에 타일이 없으면 내위치를 기준으로 i방향을 향해 반시계로 Edge를 생성한다.
			{
				FVector4 ConvertPos = TilemapComponent->TileIndexToWorldPos(FTileIndex({ cx,cy }));

				std::pair<int, int> Point1;
				std::pair<int, int> Point2;
				// TileIndex에서 Tile의 4개의 점을 중간점으로 포함할 수있도록 정수 좌표계를 확장한다.
				if (i == 0)
				{
					Point1 = { cx * 2 - 1,cy * 2 - 1 };
					Point2 = { cx * 2 + 1,cy * 2 - 1 };
				}
				else if (i == 1)
				{
					Point1 = { cx * 2 + 1,cy * 2 - 1 };
					Point2 = { cx * 2 + 1,cy * 2 + 1 };
				}
				else if (i == 2)
				{
					Point1 = { cx * 2 + 1,cy * 2 + 1 };
					Point2 = { cx * 2 - 1,cy * 2 + 1 };
				}
				else
				{
					Point1 = { cx * 2 - 1,cy * 2 + 1 };
					Point2 = { cx * 2 - 1,cy * 2 - 1 };
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

