#pragma once

#include "Core.h"

namespace FMathConst
{
	const float PI = 3.1415926535897932f;
	const double HALF_PI = PI / 2.0f;
	const double TWO_PI = PI * 2.0f;
}

class FMath
{
public:
	inline static float Sqrt(float _Value)
	{
		return std::sqrtf(_Value);
	}

	inline static double Sqrt(double _Value)
	{
		return std::sqrt(_Value);
	}

	template <typename T>
	T Max(T _Value, T _MaxValue)
	{
		return (_Value > _MaxValue) ? _MaxValue : _Value;
	}

	template <typename T>
	T ClampMin(T _Value, T _MinValue)
	{
		return (_Value < _MinValue) ? _MinValue : _Value;
	}

	template <typename T>
	static T Clamp(T _Value, T _MinValue, T _MaxValue)
	{
		if (_Value < _MinValue)
			return _MinValue;
		else if (_Value > _MaxValue)
			return _MaxValue;
		else
			return _Value;
	}

	template <typename T>
	static T Lerp(T A, T B, float Alpha)
	{
		return A * (1 - Alpha) + B * Alpha;
	}
};



