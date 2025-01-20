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

FVector2::FVector2(double _X, double _Y)
	:X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
{
}

FVector2 FVector2::operator+(const FVector2& _Other) const
{
	return FVector2(X + _Other.X, Y + _Other.Y);
}

FVector2 FVector2::operator-() const
{
	return FVector2(-X, -Y);
}

FVector2 FVector2::operator-(const FVector2& _Other) const
{
	return FVector2(X - _Other.X, Y - _Other.Y);
}

FVector2 FVector2::operator*(const float& _Value) const
{
	return FVector2(X * _Value, Y * _Value);
}

FVector2 FVector2::operator/(const float& _Value) const
{
	return FVector2(X / _Value, Y / _Value);
}

void FVector2::operator+=(const FVector2& _Other)
{
	*this = *this + _Other;
}

void FVector2::operator-=(const FVector2& _Other)
{
	*this = *this - _Other;
}

void FVector2::operator*=(const float& _Value)
{
	*this = *this * _Value;
}

void FVector2::operator*=(const FVector2& _Other)
{
	X *= _Other.X;
	Y *= _Other.Y;
}

void FVector2::operator/=(const float& _Value)
{
	*this *= 1.0f / _Value;
}

