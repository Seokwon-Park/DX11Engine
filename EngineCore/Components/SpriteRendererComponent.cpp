#include "EnginePCH.h"
#include "SpriteRendererComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ResourceManager.h>

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
		FVector4 Scale = FVector4(SpriteData.Texture->GetTextureSize(), 1.0f, 0.0f);
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
	if (_SortingLayer == SortingLayer && OrderInLayer == _OrderInLayer)
	{
		return;
	}
	std::pair<int, int> PrevOrder = std::make_pair(static_cast<int>(SortingLayer), OrderInLayer);
	SortingLayer = _SortingLayer;
	OrderInLayer = _OrderInLayer;
	int SortingLayerInt = static_cast<int>(_SortingLayer);
	std::shared_ptr<USpriteRendererComponent> RendererPtr = GetThis<USpriteRendererComponent>();
	ULevel* Level = GetOwner()->GetLevel();
	//처음 렌더러 생성시에는 Level이 Null일 수 있으므로 BeginPlay에서 처리해준다.
	if (Level == nullptr)
	{
		return;
	}
	Level->ChangeRenderOrder(PrevOrder, RendererPtr);
}

void USpriteRendererComponent::BeginPlay()
{
	URendererComponent::BeginPlay();
	GetOwner()->GetLevel()->PushRenderer(GetThis<USpriteRendererComponent>());
}

void USpriteRendererComponent::Render(float _DeltaTime)
{
	Shader->SetSpriteConstants(SpriteData.Rect);
	SpriteData.Texture->Bind();
	URendererComponent::Render(_DeltaTime);
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);


}



