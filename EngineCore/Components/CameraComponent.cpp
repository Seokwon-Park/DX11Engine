#include "EnginePCH.h"
#include "CameraComponent.h"

UCameraComponent::UCameraComponent()
{
}

UCameraComponent::~UCameraComponent()
{
}

void UCameraComponent::CalculateView()
{
	ViewMat.MatrixView(Transform.Location, FVector4::FORWARD, FVector4::UP);
}

void UCameraComponent::CalculateProj()
{
	ProjMat.MatrixOrthoLH(1280.0f,720.0f,0.1f, 100.0f);
	//ProjMat.MatrixPerspectiveProj(1280, 720, 0.1f, 10.0f);
}

FMatrix UCameraComponent::GetViewMatrix()
{
	return ViewMat;
}

FMatrix UCameraComponent::GetProjMatrix()
{
	return ProjMat;
}

