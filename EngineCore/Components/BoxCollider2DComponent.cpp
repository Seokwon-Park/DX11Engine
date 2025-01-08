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

	FSpriteRect Temp = FSpriteRect();
	auto test = FColor(1.0f, 1.0f, 1.0f, 1.0f);
	ColliderDebugRenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
	ColliderDebugRenderUnit->SetConstantBufferData("SpriteData", EShaderType::VS, Temp);
	ColliderDebugRenderUnit->SetConstantBufferData("PSColor", EShaderType::PS, test);
	ColliderDebugRenderUnit->SetSampler("PSSampler", EShaderType::PS, UEngineSamplerState::Create());

	ColliderDebugRenderUnit->Render(_Camera, _DeltaTime);
}

void UBoxCollider2DComponent::BeginPlay()
{
	USceneComponent::BeginPlay();

	ColliderDebugRenderUnit = std::make_shared<URenderUnit>();
	ColliderDebugRenderUnit->Init("Quad", "ColliderDebug");

	dynamicBox = b2MakeBox(10.0f, 10.0f);
	shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
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
		BodyDef.type = b2_staticBody;
		BodyDef.position = { Parent->GetLocation().X, Parent->GetLocation().Y };
		BodyId = b2CreateBody(GetOwner()->GetLevel()->GetPhysicsWorld(), &BodyDef);
		b2CreatePolygonShape(BodyId, &shapeDef, &dynamicBox);
	}
}

void UBoxCollider2DComponent::TickComponent(float _DeltaTime)
{
	USceneComponent::TickComponent(_DeltaTime);
	std::cout << b2Body_GetPosition(BodyId).x << ',' << b2Body_GetPosition(BodyId).y << '\n';


}


