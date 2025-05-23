#pragma once

#include "EngineBase/EngineBase.h"

#include <DirectXMath.h>
#include <ostream>

//float4 Vector
class BASE_API FVector4
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float V[4];
		DirectX::XMFLOAT4A XMFloat;
	};

	//Left handed
	static const FVector4 ZERO;
	static const FVector4 LEFT;
	static const FVector4 RIGHT;
	static const FVector4 UP;
	static const FVector4 DOWN;
	static const FVector4 FORWARD;
	static const FVector4 BACK;

	FVector4();
	FVector4(float _X, float _Y);
	FVector4(float _X, float _Y, float _Z);
	FVector4(float _X, float _Y, float _Z, float _W);
	FVector4(int _X, int _Y);
	FVector4(int _X, int _Y, int _Z);
	FVector4(long _X, long _Y);
	FVector4(long _X, long _Y, long _Z);
	FVector4(class FVector2 _XY, float _Z, float _W);

	static float Dot(const FVector4& _Left, const FVector4& _Right);
	static float Length(const FVector4& _Value);
	static FVector4 Cross(const FVector4& _Left, const FVector4& _Right);
	static FVector4 Normalize(FVector4 _Value);

	float Dot(const FVector4& _Other) const;
	float Length() const;
	FVector4 Normalize();



	//operators
	inline static friend std::ostream& operator<<(std::ostream& _Ostream, const FVector4& _Vector)
	{
		_Ostream << "(" << _Vector.X << ", " << _Vector.Y << ", " << _Vector.Z << ")";
		return _Ostream;
	}

	FVector4 operator+(const FVector4& _Other) const;
	FVector4 operator-() const;
	FVector4 operator-(const FVector4& _Other) const;
	FVector4 operator*(const float& _Value) const;
	FVector4 operator/(const float& _Value) const;
	
	float operator[](const int& _Value) const;
	float& operator[](const int& _Value);

	void operator+=(const FVector4& _Other);
	void operator-=(const FVector4& _Other);
	void operator*=(const float& _Value);
	void operator/=(const float& _Value);
};

