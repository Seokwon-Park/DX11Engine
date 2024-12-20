#pragma once
#include "SceneComponent.h"

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
	std::shared_ptr<class VertexBuffer> Test;
	std::shared_ptr<class IndexBuffer> Test2;
	std::shared_ptr<class EngineShader> Test3;


};

