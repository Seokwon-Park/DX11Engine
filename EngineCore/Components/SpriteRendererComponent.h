#pragma once
#include "RendererComponent.h"
#include <EngineCore/Resources/EngineSprite.h>

enum class ESortingLayer
{
	Default = 0,
	UI = 1000,
};


// 설명 :
class USpriteRendererComponent : public URendererComponent
{
public:
	// constrcuter destructer
	ENGINE_API USpriteRendererComponent();
	ENGINE_API ~USpriteRendererComponent();

	// delete Function
	USpriteRendererComponent(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent(USpriteRendererComponent&& _Other) noexcept = delete;
	USpriteRendererComponent& operator=(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent& operator=(USpriteRendererComponent&& _Other) noexcept = delete;

	ENGINE_API void SetSprite(UEngineSprite* _Sprite, Uint32 _Index);
	ENGINE_API void SetSprite(std::string_view _Name, Uint32 _Index);
	ENGINE_API void SetSprite(std::shared_ptr<UEngineSprite> _Sprite, Uint32 _Index);

	ENGINE_API void SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer = 0);
	ENGINE_API inline std::pair<int,int> GetOrder() { return std::make_pair(static_cast<int>(SortingLayer), OrderInLayer); }

	inline void SetAutoScale(bool _IsAutoScale) { IsAutoScale = _IsAutoScale; }
	//Material: 렌더링에 사용될 재질.
	//Bounds : 렌더러의 경계 영역.(?)
	//Sorting Layer : 2D 렌더링 시 레이어를 정렬.
	//Sorting Order : 같은 레이어에서의 렌더 순서.
protected:
	ENGINE_API void BeginPlay() override;
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime) override;
	virtual void TickComponent(float _DeltaTime)override;

private:
	UEngineSprite* Sprite;
	ESortingLayer SortingLayer = ESortingLayer::Default;
	int OrderInLayer = 0;
	bool IsAutoScale = true;
	FSpriteData SpriteData;

};

