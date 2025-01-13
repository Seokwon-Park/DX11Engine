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
	// �� Ÿ���� �ε����� ���� ���� ��ǥ�� ��ȯ- >static body�� �浹ü�� �����Ѵ�
	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;
		Index.Key = TilePair.first;

		dynamicBox = b2MakeBox(TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f, TilemapComponent->ImageSize.Y / FMath::BOX2DSCALE / 2.0f);
		shapeDef = b2DefaultShapeDef();
		shapeDef.density = 0.5f;
		shapeDef.friction = 0.0f;
		//�� ���̾�
		//shapeDef.filter.categoryBits = Layer;
		//���� �浹�ϸ� �ε����� �Ǵ� �ֵ� ��Ʈ����ŷ
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
		b2BodyId BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		b2CreatePolygonShape(BodyId, &shapeDef, &dynamicBox);
		BodyIds.push_back(BodyId);
	}

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
}

