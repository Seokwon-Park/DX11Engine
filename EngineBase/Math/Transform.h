#pragma once
#include "Vector4.h"
#include "Matrix.h"

class FTransform
{
public:
	FVector4 Location;
	FVector4 Rotation;
	FVector4 Scale;

	FMatrix WorldMatrix;
};

