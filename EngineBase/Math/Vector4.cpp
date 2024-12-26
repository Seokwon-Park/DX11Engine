#include "EnginePCH.h"

#include "Vector4.h"

#include "MathUtility.h"

const FVector4 FVector4::ZERO = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::LEFT = FVector4(-1.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::RIGHT = { 1.0f, 0.0f };
const FVector4 FVector4::UP = { 0.0f, 1.0f ,0.0f, 0.0f};
const FVector4 FVector4::DOWN = { 0.0f, -1.0f };
const FVector4 FVector4::FORWARD = { 0.0f, 0.0f, 1.0f };
const FVector4 FVector4::BACK = { 0.0f, 0.0f , -1.0f };

FVector4::FVector4()
	:FVector4(0.0f, 0.0f, 0.0f, 0.0f) {
}

FVector4::FVector4(float _X, float _Y)
	:FVector4(_X, _Y, 0.0f, 0.0f) {
}

FVector4::FVector4(float _X, float _Y, float _Z)
	:FVector4(_X, _Y, _Z, 0.0f) {
}

FVector4::FVector4(float _X, float _Y, float _Z, float _W)
	:X(_X), Y(_Y), Z(_Z), W(_W) {
}

FVector4::FVector4(int _X, int _Y)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), 0.0f, 0.0f) {
}

FVector4::FVector4(int _X, int _Y, int _Z)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), static_cast<float>(_Z), 0.0f) {
}

FVector4::FVector4(long _X, long _Y)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), 0.0f, 0.0f) {
}

FVector4::FVector4(long _X, long _Y, long _Z)
	:FVector4(static_cast<float>(_X), static_cast<float>(_Y), static_cast<float>(_Z), 0.0f) {
}

float FVector4::Dot(const FVector4& _Left, const FVector4& _Right)
{
	return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
}

float FVector4::Length(const FVector4& _Value)
{
	return FMath::Sqrt(_Value.Length());
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

float FVector4::Dot(const FVector4& _Other) const
{
	return X * _Other.X + Y * _Other.Y;
}

float FVector4::Length() const
{
	return X * X + Y * Y + Z * Z;
}

FVector4 FVector4::operator+(const FVector4& _Other) const
{
	return FVector4(X + _Other.X, Y + _Other.Y, Z + _Other.Z);
}

FVector4 FVector4::operator-() const
{
	return FVector4(-X, -Y, -Z, W);
}

FVector4 FVector4::operator-(const FVector4& _Other) const
{
	return FVector4(X - _Other.X, Y - _Other.Y, Z - _Other.Z);
}

FVector4 FVector4::operator*(const float& _Value) const
{
	return FVector4(X * _Value, Y * _Value, Z * _Value);
}

FVector4 FVector4::operator/(const float& _Value) const
{
	return FVector4(X / _Value, Y / _Value, Z / _Value);
}

float FVector4::operator[](const int& _Value) const
{
	return V[_Value];
}

float& FVector4::operator[](const int& _Value)
{
	return V[_Value];
}

void FVector4::operator+=(const FVector4& _Other)
{
	// X += _Other.X;
	// Y += _Other.Y;
	// Z += _Other.Z;
	*this = *this + _Other;
}

void FVector4::operator-=(const FVector4& _Other)
{
	// X -= _Other.X;
	// Y -= _Other.Y;
	// Z -= _Other.Z;
	*this = *this - _Other;
}

void FVector4::operator*=(const float& _Value)
{
	// X *= _Value;
	// Y *= _Value;
	// Z *= _Value;
	*this = *this * _Value;
}

void FVector4::operator/=(const float& _Value)
{
	// X /= _Value;
	// Y /= _Value;
	// Z /= _Value;
	*this *= 1.0f / _Value;
}

std::ostream& operator<<(std::ostream& _Ostream, const FVector4& _Vector)
{
	_Ostream << "(" << _Vector.X << ", " << _Vector.Y << ", " << _Vector.Z << ")";
	return _Ostream;
}
