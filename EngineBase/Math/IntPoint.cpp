#include "EnginePCH.h"
#include "IntPoint.h"

const FIntPoint FIntPoint::LEFT = { -1, 0 };
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };

FIntPoint::FIntPoint()
	:FIntPoint(0, 0) {
}

FIntPoint::FIntPoint(int _X, int _Y)
	:X(_X), Y(_Y) {
}

FIntPoint FIntPoint::operator+(const FIntPoint& _Other) const
{
	return FIntPoint(X + _Other.X, Y + _Other.Y);
}

FIntPoint FIntPoint::operator-(const FIntPoint& _Other) const
{
	return FIntPoint(X - _Other.X, Y - _Other.Y);
}

FIntPoint FIntPoint::operator/(int _Value) const
{
	return FIntPoint(X / _Value, Y / _Value);
}

void FIntPoint::operator+=(const FIntPoint& _Other)
{
	*this = *this + _Other;
}

void FIntPoint::operator-=(const FIntPoint& _Other)
{
	*this = *this - _Other;
}

