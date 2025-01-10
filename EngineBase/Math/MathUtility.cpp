#include "EnginePCH.h"
#include "MathUtility.h"
#include "Vector4.h"

const float FMath::PI = 3.1415926535897932f;
const float FMath::HALF_PI = PI / 2.0f;
const float FMath::TWO_PI = PI * 2.0f;
const float FMath::BOX2DSCALE = 100.0f;

FVector4 FMath::DegreeToRadian(FVector4 _DegreeVec4)
{
	FVector4 Result;
	Result.X = DegreeToRadian(_DegreeVec4.X);
	Result.Y = DegreeToRadian(_DegreeVec4.Y);
	Result.Z = DegreeToRadian(_DegreeVec4.Z);
	return Result;
}

FVector4 FMath::RadianToDegree(FVector4 _RadianVec4)
{
	FVector4 Result;
	Result.X = RadianToDegree(_RadianVec4.X);
	Result.Y = RadianToDegree(_RadianVec4.Y);
	Result.Z = RadianToDegree(_RadianVec4.Z);
	return Result;
}
