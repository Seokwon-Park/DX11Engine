#include "EnginePCH.h"
#include "BoxCollider2DComponent.h"
//삭제
#include "SpriteRendererComponent.h"

UBoxCollider2DComponent::UBoxCollider2DComponent()
{
}

UBoxCollider2DComponent::~UBoxCollider2DComponent()
{
}

void UBoxCollider2DComponent::DebugRender(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	auto& Test = Parent->GetTransformRef();
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj = _Camera->GetProjMatrix();
	VC.Proj.MatrixTranspose();

	float Temp[4] = { 0.5f,0.5f,0.0f,0.0f };
	auto test = FColor(0.0f, 1.0f, 0.0f, 1.0f);
	ColliderDebugRenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
	ColliderDebugRenderUnit->SetConstantBufferData("Offset", EShaderType::VS, Temp);
	ColliderDebugRenderUnit->SetConstantBufferData("DebugColor", EShaderType::PS, test);

	ColliderDebugRenderUnit->Render(_Camera, _DeltaTime);
}

void UBoxCollider2DComponent::BeginPlay()
{
	UCollider2DComponent::BeginPlay();

	ColliderDebugRenderUnit = std::make_shared<URenderUnit>();
	ColliderDebugRenderUnit->Init("Quad", "ColliderDebug");

	dynamicBox = b2MakeBox(GetTransformRef().Scale.X / FMath::BOX2DSCALE / 2.0f, GetTransformRef().Scale.Y / FMath::BOX2DSCALE / 2.0f);
	shapeDef = b2DefaultShapeDef();
	shapeDef.density = 0.5f;
	shapeDef.friction = 0.0f;
	//내 레이어
	shapeDef.filter.categoryBits = Layer;
	//내가 충돌하면 부딪혀야 되는 애들 비트마스킹
	//shapeDef.filter.maskBits = Layer;
	if (Rigidbody2D != nullptr)
	{
		BodyId = Rigidbody2D->GetBodyId();
		b2CreatePolygonShape(BodyId, &shapeDef, &dynamicBox);
	}
	else
	{
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

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UBoxCollider2DComponent>());
}

void UBoxCollider2DComponent::TickComponent(float _DeltaTime)
{
	UCollider2DComponent::TickComponent(_DeltaTime);
	if (b2Body_GetType(BodyId) == b2_kinematicBody)
	{
		b2Body_SetTransform(BodyId, b2Vec2(Parent->GetLocation().X / FMath::BOX2DSCALE, Parent->GetLocation().Y / FMath::BOX2DSCALE), b2Body_GetRotation(BodyId));
	}
}


