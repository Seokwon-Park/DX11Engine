#pragma once
#include "Vector4.h"
#include "Matrix.h"

class FTransform
{
public:
	BASE_API void UpdateTransform();
	BASE_API void UpdateTransform(FMatrix _ParentWorld);

	FVector4 Location;
	//Rotation은 Degree값을 기반으로 하기 때문에 Radian으로 변환해야 한다.
	FVector4 Rotation;
	FVector4 Scale = FVector4(1.0f,1.0f,1.0f,1.0f);

	FMatrix WorldMatrix;

	FVector4 GetFoward()
	{
		return FVector4::Normalize(WorldMatrix.Rows[2]);
	}

	FVector4 GetRight()
	{
		return FVector4::Normalize(WorldMatrix.Rows[0]);
	}

	FVector4 GetUp()
	{
		return FVector4::Normalize(WorldMatrix.Rows[1]);
	}
};

