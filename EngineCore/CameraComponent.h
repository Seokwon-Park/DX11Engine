#pragma once
#include "SceneComponent.h"

// Ŭ���� ���� :
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

	void GetViewMatrix();
	void GetProjMatrix();
protected:

private:

};
