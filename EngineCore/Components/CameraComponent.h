#pragma once

#include "SceneComponent.h"

enum class EProjectionType
{
	Orthographic,
	Perspective,
};

// 클래스 설명 :
class UCameraComponent : public USceneComponent
{
public:
	// Constrcuter Destructer
	UCameraComponent();
	~UCameraComponent();

	// Delete Function
	UCameraComponent(const UCameraComponent& _Other) = delete;
	UCameraComponent(UCameraComponent&& _Other) noexcept = delete;
	UCameraComponent& operator=(const UCameraComponent& _Other) = delete;
	UCameraComponent& operator=(UCameraComponent&& _Other) noexcept = delete;

	void CalculateView();
	void CalculateProj();
	ENGINE_API FMatrix GetViewMatrix();
	ENGINE_API FMatrix GetProjMatrix();
	FIntPoint ScreenToWorld(FIntPoint screenPosition);
	//FVector2 WorldToScreen(FVector2 worldPosition);

	inline void SetProjectionType(EProjectionType _ProjectionType) { ProjectionType = _ProjectionType; }
protected:
private:
	EProjectionType ProjectionType = EProjectionType::Orthographic;

	FMatrix ViewMat;
	FMatrix ProjMat;
};
