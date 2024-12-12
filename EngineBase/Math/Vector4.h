#pragma once

#include "MathUtility.h"
#include "Core.h"



//using float = float;
class ENGINE_API FVector4
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
	};

	inline static friend std::ostream& operator<<(std::ostream& os, const FVector4& Vector)
	{
		os << '(' << Vector.X << ',' << Vector.Y << ',' << Vector.Z << ')';
		return os;
	}

	FVector4();
	FVector4(float _X, float _Y);
	FVector4(float _X, float _Y, float _Z);
	FVector4(float _X, float _Y, float _Z, float _W);
	FVector4(int _X, int _Y);
	FVector4(int _X, int _Y, int _Z);
	FVector4(long _X, long _Y);
	FVector4(long _X, long _Y, long _Z);

	static float Dot(const FVector4& _Left, const FVector4& _Right);
	static float Length(const FVector4& _Value);
	static FVector4 Cross(const FVector4& _Left, const FVector4& _Right);
	static FVector4 Normalize(FVector4 _Value);

	////left handed
	//static const tvector4 zero;
	//static const tvector4 left;
	//static const tvector4 right;
	//static const tvector4 up;
	//static const tvector4 down;
	//static const tvector4 forward;
	//static const tvector4 back;
};

