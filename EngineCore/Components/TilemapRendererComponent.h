#pragma once
#include "RendererComponent.h"

// Ό³Έν :
class UTilemapRendererComponent : public URendererComponent
{
public:
	// constrcuter destructer
	UTilemapRendererComponent();
	~UTilemapRendererComponent();

	// delete Function
	UTilemapRendererComponent(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent(UTilemapRendererComponent&& _Other) noexcept = delete;
	UTilemapRendererComponent& operator=(const UTilemapRendererComponent& _Other) = delete;
	UTilemapRendererComponent& operator=(UTilemapRendererComponent&& _Other) noexcept = delete;

protected:

private:

};

