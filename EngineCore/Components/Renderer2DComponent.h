#pragma once
#include "RendererComponent.h"
#include <EngineCore/Enums/EngineLayer.h>


// ���� :
class URenderer2DComponent : public URendererComponent
{
public:
	// constrcuter destructer
	URenderer2DComponent();
	~URenderer2DComponent();

	// delete Function
	URenderer2DComponent(const URenderer2DComponent& _Other) = delete;
	URenderer2DComponent(URenderer2DComponent&& _Other) noexcept = delete;
	URenderer2DComponent& operator=(const URenderer2DComponent& _Other) = delete;
	URenderer2DComponent& operator=(URenderer2DComponent&& _Other) noexcept = delete;

	ENGINE_API virtual void SetOrder(ESortingLayer _SortingLayer, int _OrderInLayer = 0);
	ENGINE_API inline std::pair<int, int> GetOrder() { return std::make_pair(static_cast<int>(SortingLayer), OrderInLayer); }

	virtual void TickComponent(float _DeltaTime) override;
	virtual void BeginPlay()override;
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime);
protected:
	std::pair<int, int> PrevOrder;
	//Sorting Layer : 2D ������ �� ���̾� ����.
	//OrderInLayer : ���� ���̾���� ���� ����
	ESortingLayer SortingLayer = ESortingLayer::Default;
	int OrderInLayer = 0;
private:

};

