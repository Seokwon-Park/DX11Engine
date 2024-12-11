#include "EnginePCH.h"
#include "MathUtility.h"

std::ostream& operator<<(std::ostream& os, const FVector4& Vector)
{
	os << Vector.X << Vector.Y << Vector.Z;
	return os;
}

const FIntPoint FIntPoint::LEFT = { -1, 0 };
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };


const UColor UColor::WHITE = { 255, 255, 255, 0 };
const UColor UColor::BLACK = { 0, 0, 0, 0 };

