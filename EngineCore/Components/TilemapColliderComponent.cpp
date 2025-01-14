#include "EnginePCH.h"
#include "TilemapColliderComponent.h"

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
	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;
		Index.Key = TilePair.first;

		dynamicBox = b2MakeRoundedBox(TilemapComponent->ImageSize.X + 2.0f / FMath::BOX2DSCALE / 2.0f, TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f, 0.01f);
		ShapeDef = b2DefaultShapeDef();
		ShapeDef.density = 0.5f;
		ShapeDef.friction = 1.0f;
		//내 레이어
		//shapeDef.filter.categoryBits = Layer;
		//내가 충돌하면 부딪혀야 되는 애들 비트마스킹
		//shapeDef.filter.maskBits = Layer;

		FVector4 ConvertPos;
		ConvertPos.X = Index.X * TilemapComponent->ImageSize.X + TilemapComponent->ImageSize.X / 2.0f;
		ConvertPos.Y = Index.Y * TilemapComponent->ImageSize.Y + TilemapComponent->ImageSize.Y / 2.0f;

		b2BodyDef BodyDef = b2DefaultBodyDef();
		BodyDef.type = b2_staticBody;
		BodyDef.position = { ConvertPos.X / FMath::BOX2DSCALE,ConvertPos.Y / FMath::BOX2DSCALE };
		//BodyDef.rotation = b2MakeRot(FMath::DegreeToRadian(10.0f));
		//Parent->GetTransformRef().Rotation = FVector4(0.0f, 0.0f, FMath::DegreeToRadian(10.0f), 1.0f);
		//Parent->UpdateTransform();
		//BodyDef.fixedRotation = true;
		b2BodyId NewBodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		b2CreatePolygonShape(NewBodyId, &ShapeDef, &dynamicBox);
		BodyIds.push_back(NewBodyId);

	}
	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////
	b2BodyDef D = b2DefaultBodyDef();
	b2BodyId TestBodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &D);
	//b2ChainSegment chainSegment = { 0 };
	//chainSegment.ghost1 = b2Vec2(1.7f, 0.0f);
	//chainSegment.segment = b2Segment({ 1.0f, 0.25f }, { 0.0f, 0.0f });
	//chainSegment.ghost2 = b2Vec2(-1.7f, 0.4f);

	//b2ChainDef Def = b2DefaultChainDef();
	dynamicBox = b2MakeBox(GetTransformRef().Scale.X / FMath::BOX2DSCALE / 2.0f, GetTransformRef().Scale.Y / FMath::BOX2DSCALE / 2.0f);
	b2Vec2 points[6] = {
	{10.0f, 0.0f},
	{1.0f, 0.0f},
	{-1.0f, 0.0f},
	{-2.0f, 0.0f},
	{-3.0f, 1.0f},

	{-10.0f, 0.0f} };

	b2Vec2 v1 = { -2.0f, 0.0f };
	b2Vec2 v2 = { 2.0f, 0.0f };
	b2Vec2 v3 = { 2.0f, -4.0f };
	b2Vec2 v4 = { -2.0f, -4.0f };

	//반시계 방향으로 정점을 돌려야 바깥쪽으로 collide한다.
	b2Vec2 points2[7] = {
		v1,v4,v3,v2,v1,v4,v3
	};

	b2ChainDef chainDef = b2DefaultChainDef();
	chainDef.points = points2;
	chainDef.count = 7;

	b2ChainId myChainId = b2CreateChain(TestBodyId, &chainDef);

	//b2CreateChain(TestBodyId, &Def);
	///////////////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////	////////////////////////////////
	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
}

