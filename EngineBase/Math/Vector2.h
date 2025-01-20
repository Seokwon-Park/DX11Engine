#pragma once

#include <DirectXMath.h>
#include <EngineBase/EngineBase.h>
#include "Vector4.h"

class BASE_API FVector2
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
		};
		float V[2];
		DirectX::XMFLOAT2 XMFloat;
	};

	static const FVector2 ZERO;
	static const FVector2 LEFT;
	static const FVector2 RIGHT;
	static const FVector2 UP;
	static const FVector2 DOWN;

	FVector2();
	FVector2(int _X, int _Y);
	FVector2(float _X, float _Y);
	FVector2(double _X, double _Y);

	static friend std::ostream& operator<<(std::ostream& _Ostream, const FVector2& _Vector)
	{
		_Ostream << "(" << _Vector.X << ", " << _Vector.Y << ")";
		return _Ostream;
	}

	FVector2 operator+(const FVector2& _Other) const;
	FVector2 operator-() const;
	FVector2 operator-(const FVector2& _Other) const;
	FVector2 operator*(const float& _Value) const;
	FVector2 operator/(const float& _Value) const;

	void operator+=(const FVector2& _Other);
	void operator-=(const FVector2& _Other);
	void operator*=(const float& _Value);
	void operator*=(const FVector2& _Other);
	void operator/=(const float& _Value);

};

