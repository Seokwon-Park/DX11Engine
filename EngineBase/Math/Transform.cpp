#include "EnginePCH.h"
#include "Transform.h"


void FTransform::UpdateTransform()
{
	FMatrix A;
	FMatrix B;
	FMatrix C;

	C.MatrixScaling(Scale);
	B.MatrixRotation(Rotation);
	A.MatrixTranslation(Location);

	WorldMatrix = A * B * C;
}