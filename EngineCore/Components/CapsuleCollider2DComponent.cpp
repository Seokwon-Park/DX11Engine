#include "EnginePCH.h"
#include "CapsuleCollider2DComponent.h"
#include <EngineCore/Structures/ShaderBufferDataStructure.h>

UCapsuleCollider2DComponent::UCapsuleCollider2DComponent()
{
}

UCapsuleCollider2DComponent::~UCapsuleCollider2DComponent()
{
}



void UCapsuleCollider2DComponent::BeginPlay()
{
	UCollider2DComponent::BeginPlay();

	ColliderDebugRenderUnit = std::make_shared<URenderUnit>();
	ColliderDebugRenderUnit->Init("ColliderBoxDebug", "ColliderDebug");

	Radius = GetTransformRef().Scale.X / FMath::BOX2DSCALE / 2.0f;
	float ScaleY = GetTransformRef().Scale.Y / FMath::BOX2DSCALE / 2.0f;

	CapsuleShape.center1 = b2Vec2( 0.0f, ScaleY - Radius);
	CapsuleShape.center2 = b2Vec2( 0.0f, -ScaleY + Radius);
	CapsuleShape.radius = Radius;

	ShapeDef =  b2DefaultShapeDef();
	ShapeDef.density = 1.0f;
	ShapeDef.friction = 1.0f;
	ShapeDef.rollingResistance = 1.0f;

	//내 레이어
	//shapeDef.filter.categoryBits = Layer;
	//내가 충돌하면 부딪혀야 되는 애들 비트마스킹
	//shapeDef.filter.maskBits = Layer;
	if (Rigidbody2D != nullptr)
	{
		BodyId = Rigidbody2D->GetBodyId();
		b2CreateCapsuleShape(BodyId, &ShapeDef, &CapsuleShape);
	}
	else
	{
		b2BodyDef BodyDef = b2DefaultBodyDef();
		BodyDef.type = b2_kinematicBody;
		BodyDef.position = { Parent->GetLocation().X / FMath::BOX2DSCALE, Parent->GetLocation().Y / FMath::BOX2DSCALE };
		//BodyDef.rotation = b2MakeRot(FMath::DegreeToRadian(10.0f));
		//Parent->GetTransformRef().Rotation = FVector4(0.0f, 0.0f, FMath::DegreeToRadian(10.0f), 1.0f);
		//Parent->UpdateTransform();
		BodyDef.fixedRotation = true;
		BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		b2CreateCapsuleShape(BodyId, &ShapeDef, &CapsuleShape);
	}

	GetOwner()->GetLevel()->PushCollider2D(GetThis<UCapsuleCollider2DComponent>());
}

void UCapsuleCollider2DComponent::DebugRender(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	auto& Test = Parent->GetTransformRef();
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj = _Camera->GetProjectionMatrix();
	VC.Proj.MatrixTranspose();

	float Temp[4] = { 0.5f,0.5f,0.0f,0.0f };
	auto test = FColor(0.0f, 1.0f, 0.0f, 1.0f);
	ColliderDebugRenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
	ColliderDebugRenderUnit->SetConstantBufferData("Offset", EShaderType::VS, Temp);
	ColliderDebugRenderUnit->SetConstantBufferData("DebugColor", EShaderType::PS, test);

	ColliderDebugRenderUnit->Render(_Camera, _DeltaTime);
}

void UCapsuleCollider2DComponent::TickComponent(float _DeltaTime)
{

}