#pragma once
#include "SceneComponent.h"
#include <EngineCore/RenderUnit.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineShader.h>


// Ό³Έν :
class URendererComponent : public USceneComponent
{
	friend class ULevel;
public:
	// constrcuter destructer
	ENGINE_API URendererComponent();
	ENGINE_API ~URendererComponent();

	// delete Function
	URendererComponent(const URendererComponent& _Other) = delete;
	URendererComponent(URendererComponent&& _Other) noexcept = delete;
	URendererComponent& operator=(const URendererComponent& _Other) = delete;
	URendererComponent& operator=(URendererComponent&& _Other) noexcept = delete;

	std::shared_ptr<URenderUnit> AddRenderUnit();
	void AddRenderUnit(std::shared_ptr<URenderUnit> _RenderUnit);
	virtual void TickComponent(float _DeltaTime) override;
	virtual void BeginPlay()override;
protected:
	virtual void Render(class UCameraComponent* _Camera, float _DeltaTime);
private:
	std::vector<std::shared_ptr<URenderUnit>> RenderUnits;

};

