#include "EnginePCH.h"
#include "Renderer2DComponent.h"

URenderer2DComponent::URenderer2DComponent()
{
}

URenderer2DComponent::~URenderer2DComponent()
{
}

void URenderer2DComponent::SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer)
{
	if (SortingLayer == _SortingLayer && OrderInLayer == _OrderInLayer)
	{
		return;
	}
	PrevOrder = std::make_pair(static_cast<int>(SortingLayer), OrderInLayer);
	SortingLayer = _SortingLayer;
	OrderInLayer = _OrderInLayer;
}

void URenderer2DComponent::TickComponent(float _DeltaTime)
{
	URendererComponent::TickComponent(_DeltaTime);
}

void URenderer2DComponent::BeginPlay()
{
	URendererComponent::BeginPlay();

}

void URenderer2DComponent::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	URendererComponent::Render(_Camera, _DeltaTime);
}
