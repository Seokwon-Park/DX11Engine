#include "EnginePCH.h"
#include "CameraComponent.h"
#include "EngineCore.h"

UCameraComponent::UCameraComponent()
{
}

UCameraComponent::~UCameraComponent()
{
}

void UCameraComponent::CalculateView()
{
	ViewMat.MatrixView(Transform.Location, Transform.GetFoward(), Transform.GetUp());
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

ENGINE_API FMatrix UCameraComponent::GetViewMatrixTranspose()
{
	return FMatrix::Transpose(ViewMat);
}

FMatrix UCameraComponent::GetProjectionMatrix()
{
	return ProjMat;
}

ENGINE_API FMatrix UCameraComponent::GetProjectionMatrixTranspose()
{
	return FMatrix::Transpose(ProjMat);
}

ENGINE_API FMatrix UCameraComponent::GetViewProjectionMatrix()
{
	return ViewMat * ProjMat;
}

ENGINE_API FMatrix UCameraComponent::GetViewProjectionMatrixTranspose()
{
	return FMatrix::Transpose(ViewMat * ProjMat);
}

FIntPoint UCameraComponent::ScreenToWorld(FIntPoint _MousePosition)
{
	FIntPoint Size = UEngineCore::GetMainWindow().GetWindowSize();

	// 마우스 커서의 위치를 NDC로 변환
	// 마우스 커서는 좌측 상단 (0, 0), 우측 하단(width-1, height-1)
	// NDC는 좌측 하단이 (-1, -1), 우측 상단(1, 1)
	float CursorX = _MousePosition.X * 2.0f / Size.X - 1.0f;
	float CursorY = -_MousePosition.Y * 2.0f / Size.Y + 1.0f;

	CursorX = FMath::Clamp(CursorX, -1.0f, 1.0f);
	CursorY = FMath::Clamp(CursorY, -1.0f, 1.0f);

	FMatrix ViewProjectionInverse = ViewMat * ProjMat;
	ViewProjectionInverse.MatrixInverse();

	FVector4 Result = ViewProjectionInverse * FVector4(CursorX, CursorY, 0.0f, 1.0f);

	return FIntPoint(static_cast<int>(Result.X), static_cast<int>(Result.Y));
}

