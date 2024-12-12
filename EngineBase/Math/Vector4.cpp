#include "EnginePCH.h"
#include "Vector4.h"

FVector4::FVector4()
	:FVector4(0.0f, 0.0f, 0.0f, 1.0f) {}

FVector4::FVector4(float _X, float _Y)
	:FVector4(_X, _Y, 0.0f, 1.0f) {}

FVector4::FVector4(float _X, float _Y, float _Z)
	:FVector4(_X, _Y, _Z, 1.0f) {}

FVector4::FVector4(float _X, float _Y, float _Z, float _W)
	:X(_X), Y(_Y), Z(_Z), W(_W) {}

FVector4::FVector4(int _X, int _Y)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), 0.0f, 1.0f) {}
FVector4::FVector4(int _X, int _Y, int _Z)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), static_cast<float>(_Z), 1.0f) {}

FVector4::FVector4(long _X, long _Y)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), 0.0f, 1.0f) {}

FVector4::FVector4(long _X, long _Y, long _Z)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), static_cast<float>(_Z), 1.0f) {}

float FVector4::Dot(const FVector4& _Left, const FVector4& _Right)
{
	return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
}

float FVector4::Length(const FVector4& _Value)
{
	return FMath::Sqrt(_Value.X * _Value.X + _Value.Y * _Value.Y + _Value.Z * _Value.Z);
}

FVector4 FVector4::Cross(const FVector4& _Left, const FVector4& _Right)
{
	FVector4 Result;
	Result.X = _Left.Y * _Right.Z - _Left.Z * _Right.Y;
	Result.Y = _Left.Z * _Right.X - _Left.X * _Right.Z;
	Result.Z = _Left.X * _Right.Y - _Left.Y * _Right.X;
	return Result;
}

FVector4 FVector4::Normalize(FVector4 _Value)
{
	float Len = Length(_Value);
	FVector4 Result;
	Result.X /= Len;
	Result.Y /= Len;
	Result.Z /= Len;
	return Result;
}


