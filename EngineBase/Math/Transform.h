#pragma once
#include "Vector4.h"
#include "Matrix.h"

class FTransform
{
public:
	BASE_API void UpdateTransform();
	BASE_API void UpdateTransform(FMatrix _ParentWorld);

	FVector4 Location;
	FVector4 Rotation;
	FVector4 Scale = FVector4(1.0f,1.0f,1.0f,1.0f);

	FMatrix WorldMatrix;

};

