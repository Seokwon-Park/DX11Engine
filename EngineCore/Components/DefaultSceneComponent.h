#pragma once
#include "SceneComponent.h"

// 클래스 설명 :
class UDefaultSceneComponent : public USceneComponent
{
public:
	// Constrcuter Destructer
	ENGINE_API UDefaultSceneComponent();
	ENGINE_API ~UDefaultSceneComponent();

	// Delete Function
	UDefaultSceneComponent(const UDefaultSceneComponent& _Other) = delete;
	UDefaultSceneComponent(UDefaultSceneComponent&& _Other) noexcept = delete;
	UDefaultSceneComponent& operator=(const UDefaultSceneComponent& _Other) = delete;
	UDefaultSceneComponent& operator=(UDefaultSceneComponent&& _Other) noexcept = delete;
protected:

private:

};
