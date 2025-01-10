#pragma once
#include "EngineBase/EngineBase.h"
#include <cmath>

class BASE_API FMath
{
public:
	inline static float Sqrt(float _Value) { return std::sqrtf(_Value); }
	inline static double Sqrt(double _Value) { return std::sqrt(_Value); }

	inline static float SinDegreef(float _Degree) { return Sinf(DegreeToRadian(_Degree)); }
	inline static float Sinf(float _Radian) { return std::sinf(_Radian); }

	inline static float CosDegreef(float _Degree) { return Cosf(DegreeToRadian(_Degree)); }
	inline static float Cosf(float _Radian) { return std::cosf(_Radian); }
	
	inline static float DegreeToRadian(float _Degree) { return _Degree * (PI / 180.0f); }
	inline static float RadianToDegree(float _Radian) { return _Radian * (180.0f/ PI); }

	static class FVector4 DegreeToRadian(class FVector4 _DegreeVec4);
	static class FVector4 RadianToDegree(class FVector4 _RadianVec4);

	template <typename T>
	inline static T Max(T _AValue, T _BValue)
	{
		return (_AValue > _BValue) ? _AValue : _BValue;
	}

	template <typename T>
	inline static T Min(T _AValue, T _BValue)
	{
		return (_AValue < _BValue) ? _AValue : _BValue;
	}

	template <typename T>
	inline static T Clamp(T _Value, T _MinValue, T _MaxValue)
	{
		if (_Value < _MinValue)
		{
			return _MinValue;
		}
		else if (_Value > _MaxValue)
		{
			return _MaxValue;
		}
		else
		{
			return _Value;
		}
	}

	template <typename T>
	inline static T Lerp(T _A, T _B, float _Alpha)
	{
		return _A * (1 - _Alpha) + _B * _Alpha;
	}

	//Constants
	static const float PI;
	static const float HALF_PI;
	static const float TWO_PI;
	static const float BOX2DSCALE;
};



