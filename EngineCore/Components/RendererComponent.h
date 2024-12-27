#pragma once
#include "SceneComponent.h"
#include <EngineCore/Graphics/EngineBuffer.h>
#include <EngineCore/Graphics/EngineShader.h>

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

	void SetOrder(int _Order);

protected:
	ENGINE_API void BeginPlay() override;

private:
	virtual void Render(float _DeltaTime);
	std::shared_ptr<VertexBuffer> VB;
	std::shared_ptr<IndexBuffer> IB;
	std::shared_ptr<UEngineShader> Shader;


};

