#pragma once
#include "SceneComponent.h"
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

protected:
	ENGINE_API void BeginPlay() override;
	virtual void Render(float _DeltaTime);

	std::shared_ptr<UEngineVertexBuffer> VB;
	std::shared_ptr<UEngineIndexBuffer> IB;
	std::shared_ptr<UEngineShader> VS;
	std::shared_ptr<UEngineShader> PS;

private:


};

