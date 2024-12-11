#pragma once

const float PI = 3.1415926535897932f;
const double HALF_PI = 3.1415926535897932f;
const double TWO_PI = 6.28318530717f;



class /*__declspec(dllexport)*/ FMath
{
public:
	// 상수 정의

	const float PI;
	const float PI2;

	inline static float Sqrt(float _value)
	{
		return std::sqrtf(_value);
	}

	template <typename T>
	T Max(T _value, T _maxValue)
	{
		return (_value > _maxValue) ? _maxValue : _value;
	}

	template <typename T>
	T ClampMin(T _value, T _minValue)
	{
		return (_value < _minValue) ? _minValue : _value;
	}

	template <typename T>
	static T Clamp(T _value, T _minValue, T _maxValue)
	{
		if (_value < _minValue)
			return _minValue;
		else if (_value > _maxValue)
			return _maxValue;
		else
			return _value;
	}

	template <typename T>
	static T Lerp(T A, T B, float Alpha)
	{
		return A * (1 - Alpha) + B * Alpha;
	}
};






enum class ECollisionType
{
	Point,
	Rect,
	CirCle, // 타원이 아닌 정방원 
	Max

	//AABB,
	//OBB,
};

// 대부분 오브젝트에서 크기와 위치는 한쌍입니다.
//// 그래서 그 2가지를 모두 묶는 자료형을 만들어서 그걸 써요.
//class FTransform
//{
//private:
//public:
//	static bool Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right);
//
//	FVector4 Scale;
//	FVector4 Location;
//
//
//	FVector4 CenterLeftTop() const
//	{
//		return Location - Scale.Half();
//	}
//
//	FVector4 CenterLeftBottom() const
//	{
//		FVector4 Result;
//		Result.X = Location.X - Scale.hX();
//		Result.Y = Location.Y + Scale.hY();
//		return Result;
//	}
//
//	float CenterLeft() const
//	{
//		return Location.X - Scale.hX();
//	}
//
//	float CenterTop() const
//	{
//		return Location.Y - Scale.hY();
//	}
//
//	FVector4 CenterRightTop() const
//	{
//		FVector4 Result;
//		Result.X = Location.X + Scale.hX();
//		Result.Y = Location.Y - Scale.hY();
//		return Result;
//	}
//
//	FVector4 CenterRightBottom() const
//	{
//		return Location + Scale.Half();
//	}
//
//	float CenterRight() const
//	{
//		return Location.X + Scale.hX();
//	}
//
//	float CenterBottom() const
//	{
//		return Location.Y + Scale.hY();
//	}
//};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};


class UColor
{
public:
	static const UColor WHITE;
	static const UColor BLACK;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	bool operator==(const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}


	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};

