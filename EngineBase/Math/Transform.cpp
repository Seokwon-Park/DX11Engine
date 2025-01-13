#include "EnginePCH.h"
#include "Transform.h"


void FTransform::UpdateTransform()
{
	FMatrix ScaleMatrix;
	FMatrix RotateMatrix;
	FMatrix TranslationMatrix;

	ScaleMatrix.MatrixScaling(Scale);
	RotateMatrix.MatrixRotationDegree(Rotation);
	TranslationMatrix.MatrixTranslation(Location);

	WorldMatrix = ScaleMatrix * RotateMatrix * TranslationMatrix;
}

BASE_API void FTransform::UpdateTransform(FMatrix _ParentWorld)
{
	FMatrix ScaleMatrix;
	FMatrix RotateMatrix;
	FMatrix TranslationMatrix;

	ScaleMatrix.MatrixScaling(Scale);
	RotateMatrix.MatrixRotationDegree(Rotation);
	TranslationMatrix.MatrixTranslation(Location);

	WorldMatrix = ScaleMatrix * RotateMatrix * TranslationMatrix * _ParentWorld;
}
