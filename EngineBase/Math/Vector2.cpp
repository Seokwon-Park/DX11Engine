#include "EnginePCH.h"
#include "Vector2.h"

const FVector2 FVector2::ZERO = FVector2(0.0f, 0.0f);
const FVector2 FVector2::LEFT = FVector2(-1.0f, 0.0f);
const FVector2 FVector2::RIGHT = FVector2(1.0f, 0.0f);
const FVector2 FVector2::UP = FVector2(0.0f, 1.0f);
const FVector2 FVector2::DOWN = FVector2(0.0f, -1.0f);


FVector2::FVector2()
	:X(0.0f), Y(0.0f)
{

}
FVector2::FVector2(int _X, int _Y)
	:X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
{

}
FVector2::FVector2(float _X, float _Y)
	:X(_X), Y(_Y)
{

}

FVector2 FVector2::operator*(const float& _Value) const
{
	return FVector2(X * _Value, Y * _Value);
}

