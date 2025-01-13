#include "EnginePCH.h"
#include "TilemapColliderComponent.h"

UTilemapColliderComponent::UTilemapColliderComponent()
{
}

UTilemapColliderComponent::~UTilemapColliderComponent()
{
}

void UTilemapColliderComponent::BeginPlay()
{

	// �� Ÿ���� �ε����� ���� ���� ��ǥ�� ��ȯ- >static body�� �浹ü�� �����Ѵ�
	for (std::pair<const __int64, FTileData>& TilePair : TilemapComponent->Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		dynamicBox = b2MakeBox(TilemapComponent->ImageSize.X / FMath::BOX2DSCALE / 2.0f, TilemapComponent->ImageSize.Y / FMath::BOX2DSCALE / 2.0f);
		shapeDef = b2DefaultShapeDef();
		shapeDef.density = 0.5f;
		shapeDef.friction = 0.0f;
		//�� ���̾�
		shapeDef.filter.categoryBits = Layer;
		//���� �浹�ϸ� �ε����� �Ǵ� �ֵ� ��Ʈ����ŷ
		//shapeDef.filter.maskBits = Layer;
		b2BodyDef BodyDef = b2DefaultBodyDef();
		BodyDef.type = b2_kinematicBody;
		BodyDef.position = { Parent->GetLocation().X / FMath::BOX2DSCALE, Parent->GetLocation().Y / FMath::BOX2DSCALE };
		//BodyDef.rotation = b2MakeRot(FMath::DegreeToRadian(10.0f));
		//Parent->GetTransformRef().Rotation = FVector4(0.0f, 0.0f, FMath::DegreeToRadian(10.0f), 1.0f);
		//Parent->UpdateTransform();
		//BodyDef.fixedRotation = true;
		BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		b2CreatePolygonShape(BodyId, &shapeDef, &dynamicBox);
	}

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UTilemapColliderComponent>());
}

void UTilemapColliderComponent::TickComponent(float _DeltaTime)
{
}

