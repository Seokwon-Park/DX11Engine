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
	//ProjMat.MatrixPerspectiveProj(1280.0f, 720.0f, 0.1f, 100.0f);
	//ProjMat.MatrixPerspectiveProj(1280.0f, 720.0f, 1.0f, 100.0f);
	switch (ProjectionType)
	{
	case EProjectionType::Orthographic:
		ProjMat.MatrixOrthoLH(1280.0f, 720.0f, 1.0f, 1000.0f);
		break;
	case EProjectionType::Perspective:
		ProjMat.MatrixPerspectiveFov(60.0f, 1280.0f / 720.0f, 1.0f, 1000.0f);
		break;
	default:
		break;
	}
	//ProjMat.MatrixPerspectiveFov(70.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
}

FMatrix UCameraComponent::GetViewMatrix()
{
	return ViewMat;
}

FMatrix UCameraComponent::GetProjMatrix()
{
	return ProjMat;
}

