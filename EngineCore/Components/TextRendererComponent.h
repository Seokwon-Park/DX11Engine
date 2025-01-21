#pragma once
#include "Renderer2DComponent.h"
#include <EngineCore/Resources/EngineFont.h>

struct TextParams
{
	FColor Color = FColor(0.0f, 0.0f, 0.0f, 1.0f); // 텍스트 색상 (RGBA)
	float Kerning = 0.0f;    // 글자 간 간격
	float LineSpacing = 0.0f; // 줄 간 간격
};

// 설명 :
class UTextRendererComponent : public URenderer2DComponent
{
public:
	// constrcuter destructer
	ENGINE_API UTextRendererComponent();
	ENGINE_API ~UTextRendererComponent();

	// delete Function
	UTextRendererComponent(const UTextRendererComponent& _Other) = delete;
	UTextRendererComponent(UTextRendererComponent&& _Other) noexcept = delete;
	UTextRendererComponent& operator=(const UTextRendererComponent& _Other) = delete;
	UTextRendererComponent& operator=(UTextRendererComponent&& _Other) noexcept = delete;

	ENGINE_API virtual void SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer = 0) override;

	ENGINE_API void SetFont(std::string_view _FontName);
	ENGINE_API inline void SetText(std::string_view _Text) { Text = UEngineString::ToWString(_Text); };

	virtual void TickComponent(float _DeltaTime) override;
	virtual void BeginPlay()override;
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime);
protected:

private:
	std::shared_ptr<URenderUnit> Unit;

	TextParams TextParam;
	std::wstring Text;
	std::shared_ptr<UEngineFont> Font;
};

