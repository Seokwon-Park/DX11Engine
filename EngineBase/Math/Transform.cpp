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



	WorldMatrix = C * B * A;
}

BASE_API void FTransform::UpdateTransform(FMatrix _ParentWorld)
{
	FMatrix A;
	FMatrix B;
	FMatrix C;

	A.MatrixTranslation(Location);
	B.MatrixRotation(Rotation);
	C.MatrixScaling(Scale);

	WorldMatrix = C * B * A * _ParentWorld;
}
