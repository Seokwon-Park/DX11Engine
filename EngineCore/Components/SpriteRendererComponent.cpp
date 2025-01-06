#include "EnginePCH.h"
#include "SpriteRendererComponent.h"
#include "CameraComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ResourceManager.h>

struct VertexConstant
{
	FMatrix World;
	FMatrix View;
	FMatrix Proj;
};

USpriteRendererComponent::USpriteRendererComponent()
{
}

USpriteRendererComponent::~USpriteRendererComponent()
{
}

void USpriteRendererComponent::SetSprite(UEngineSprite* _Sprite, Uint32 _Index)
{
	Sprite = _Sprite;
	SpriteData = Sprite->GetSpriteData(_Index);
	if (true == IsAutoScale)
	{
		FVector2 TextureSize = SpriteData.Texture->GetTextureSize();
		FVector2 CuttingSize = SpriteData.Rect.CuttingSize;

		FVector4 Scale = FVector4(TextureSize.X * CuttingSize.X, TextureSize.Y * CuttingSize.Y, 1.0f, 0.0f);
		SetRelativeScale3D(Scale /** CurAnimation->AutoScaleRatio*/);
	}
}

void USpriteRendererComponent::SetSprite(std::string_view _Name, Uint32 _Index)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	SetSprite(UResourceManager::Find<UEngineSprite>(UpperName), _Index);
}

void USpriteRendererComponent::SetSprite(std::shared_ptr<UEngineSprite> _Sprite, Uint32 _Index)
{
	SetSprite(_Sprite.get(), _Index);
}

void USpriteRendererComponent::SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer)
{
	if (SortingLayer == _SortingLayer && OrderInLayer == _OrderInLayer)
	{
		return;
	}
	std::pair<int, int> PrevOrder = std::make_pair(static_cast<int>(SortingLayer), OrderInLayer);
	SortingLayer = _SortingLayer;
	OrderInLayer = _OrderInLayer;
	int SortingLayerInt = static_cast<int>(_SortingLayer);
	std::shared_ptr<USpriteRendererComponent> RendererPtr = GetThis<USpriteRendererComponent>();
	ULevel* Level = GetOwner()->GetLevel();

	//처음 렌더러 생성시에는 Level이 Null일 수 있으므로 미루고 BeginPlay에서 처리.
	if (Level == nullptr)
	{
		return;
	}
	Level->ChangeRenderOrder(PrevOrder, RendererPtr);
}

void USpriteRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
	SpriteRenderUnit = AddRenderUnit();
	SpriteRenderUnit->Init("Quad", "Quad");
	GetOwner()->GetLevel()->PushRenderer(GetThis<USpriteRendererComponent>());
}

void USpriteRendererComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View = _Camera->GetViewMatrix();
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj = _Camera->GetProjMatrix();
	VC.Proj.MatrixTranspose();

	SpriteRenderUnit->SetConstantBufferData("WorldViewProjection", EShaderType::VS, VC);
	SpriteRenderUnit->SetConstantBufferData("SpriteData", EShaderType::VS, SpriteData.Rect);
	SpriteRenderUnit->SetTexture("SpriteTexture", EShaderType::PS, SpriteData.Texture);
	SpriteRenderUnit->SetSampler("PSSampler", EShaderType::PS, UEngineSamplerState::Create());
	

	URendererComponent::Render(_Camera, _DeltaTime);
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);


}



