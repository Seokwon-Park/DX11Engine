#include "EnginePCH.h"
#include "Vector4.h"

const FVector4 FVector4::ZERO = { 0.0f, 0.0f,0.0f };
const FVector4 FVector4::LEFT = { -1.0f, 0.0f,0.0f };
const FVector4 FVector4::RIGHT = { 1.0f, 0.0f, 0.0f };
const FVector4 FVector4::UP = { 0.0f, 1.0f, 0.0f };
const FVector4 FVector4::DOWN = { 0.0f, -1.0f, 0.0f };
const FVector4 FVector4::FORWARD = { 0.0f, 0.0f, 1.0f };
const FVector4 FVector4::BACK = { 0.0f, 0.0f , -1.0f };

FVector4 FVector4::Cross(const FVector4& _Left, const FVector4& _Right)
{
	FVector4 Result;
	Result.X = _Left.Y * _Right.Z - _Left.Z * _Right.Y;
	Result.Y = _Left.Z * _Right.X - _Left.X * _Right.Z;
	Result.Z = _Left.X * _Right.Y - _Left.Y * _Right.X;
	return Result;
}

float FVector4::Dot(const FVector4& _Left, const FVector4& _Right)
{
	return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
}

FVector4 FVector4::Normalize(FVector4 _Value)
{
	_Value.Normalize();
	return _Value;
}