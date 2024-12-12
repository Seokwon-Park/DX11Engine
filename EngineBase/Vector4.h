#pragma once

using Vector4f = TVector4<float>;
using Vector4d = TVector4<double>;


template <typename T>
class TVector4
{
public:
	union
	{
		struct
		{
			T X;
			T Y;
			T Z;
			T W;
		};

		T XYZW[4];
	};

	////Left Handed
	//static const TVector4 ZERO;
	//static const TVector4 LEFT;
	//static const TVector4 RIGHT;
	//static const TVector4 UP;
	//static const TVector4 DOWN;
	//static const TVector4 FORWARD;
	//static const TVector4 BACK;

	TVector4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	TVector4(float _X, float _Y) : X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{

	}

	TVector4(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	TVector4(float _X, float _Y, float _Z, float _W) : X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

	TVector4(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	TVector4(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	static T Dot(const TVector4& _Left, const TVector4& _Right)
	{
		return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
	}
	static TVector4 Cross(const TVector4<T>& _Left, const TVector4<T>& _Right)
	{
		TVector4 Result;
		Result.X = _Left.Y * _Right.Z - _Left.Z * _Right.Y;
		Result.Y = _Left.Z * _Right.X - _Left.X * _Right.Z;
		Result.Z = _Left.X * _Right.Y - _Left.Y * _Right.X;
		return Result;
	}
	static TVector4 Normalize(TVector4 _Value);

	void Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			Y = Y / Len;
			Z = Z / Len;
		}
		return;
	}

	static float GetVectorAngleDeg(const TVector4& _Left, const TVector4& _Right)
	{
		//return GetVectorAngleRad(_Left, _Right) * FMath::R2D;
	}


	static float GetVectorAngleRad(const TVector4& _Left, const TVector4& _Right)
	{
		TVector4 LCopy = _Left;
		TVector4 RCopy = _Right;
		LCopy.Normalize();
		RCopy.Normalize();

		// Cos은 라디안인가요?
		// cos(라디안) => CosRad
		// cos(라디안)
		float CosRad = Dot(LCopy, RCopy);

		// cos 의 역함수 
		// cos(각도) => 결과
		// acos(결과) => 각도
		// cos함수의 역함수
		return acos(CosRad);
	}

	//// 360도 개념으로 넣어줘라.
	//static FVector4 AngleToVectorDeg(float _Angle)
	//{
	//	// 360분법을 => 라디안으로 바꾸는 값을 만들어야 한다.
	//	// 360 => 6.28

	//	// 라디안 각도체계를 기반으로 sinf(_Angle) cosf

	//	// 근본함수는 라디안 개념으로 만들고
	//	return AngleToVectorRad(_Angle * FMath::D2R);
	//}


	static TVector4 Lerp(TVector4 _A, TVector4 _B, float _Alpha)
	{
		TVector4 Result;
		_Alpha = FMath::Clamp(_Alpha, 0.0f, 1.0f);
		Result.X = FMath::Lerp(_A.X, _B.X, _Alpha);
		Result.Y = FMath::Lerp(_A.Y, _B.Y, _Alpha);
		return Result;
	}

	//          Rad 라디안을 넣어주면 
	// 여기에서 나온 결과값이 리턴해줄수 있는건
	// 길이가 1인 벡터이다.
	// static입니까?
	static TVector4 AngleToVectorRad(float _Angle)
	{
		// 특정 각도를 가리키는 벡터를 만들수 있다고 해죠?
		// 벡터 길이와 방향을 생각해라.
		// 방향은 정해졌는데 길이는 1인 벡터를 만들어내는 겁니다.

		// 0도일때의 밑변      0도일대의 높이

		// cosf(_Angle) = 밑변
		return { cosf(_Angle), sinf(_Angle) };
	}

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	bool IsZeroed() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	TVector4 Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	// 빗변의 길이입니다.
	float Length() const
	{
		return FMath::Sqrt(X * X + Y * Y + Z * Z);
	}

	TVector4 NormalizeReturn() const
	{
		TVector4 Result = *this;
		Result.Normalize();
		return Result;
	}

	// 
	//void RotationXDeg(float _Angle)
	//{
	//	RotationXRad(_Angle * FMath::D2R);
	//}

	//void RotationXRad(float _Angle)
	//{
	//	FVector4 Copy = *this;
	//	Z = (Copy.Z * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
	//	Y = (Copy.Z * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	//}

	//FVector4 RotationXDegReturn(float _Angle)
	//{
	//	return RotationXRadReturn(_Angle * FMath::D2R);
	//}

	//FVector4 RotationXRadReturn(float _Angle)
	//{
	//	FVector4 Result = *this;
	//	Result.Z = (Z * cosf(_Angle)) - (Y * sinf(_Angle));
	//	Result.Y = (Z * sinf(_Angle)) + (Y * cosf(_Angle));
	//	return Result;
	//}


	//// 
	//void RotationYDeg(float _Angle)
	//{
	//	RotationYRad(_Angle * FMath::D2R);
	//}

	//void RotationYRad(float _Angle)
	//{
	//	FVector4 Copy = *this;
	//	X = (Copy.X * cosf(_Angle)) - (Copy.Z * sinf(_Angle));
	//	Z = (Copy.X * sinf(_Angle)) + (Copy.Z * cosf(_Angle));
	//}

	//FVector4 RotationYDegReturn(float _Angle)
	//{
	//	return RotationYRadReturn(_Angle * FMath::D2R);
	//}

	//FVector4 RotationYRadReturn(float _Angle)
	//{
	//	FVector4 Result = *this;
	//	Result.X = (X * cosf(_Angle)) - (Z * sinf(_Angle));
	//	Result.Z = (X * sinf(_Angle)) + (Z * cosf(_Angle));
	//	return Result;
	//}

	//// 
	//void RotationZDeg(float _Angle)
	//{
	//	RotationZRad(_Angle * FMath::D2R);
	//}

	//void RotationZRad(float _Angle)
	//{
	//	FVector4 Copy = *this;
	//	X = (Copy.X * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
	//	Y = (Copy.X * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	//}

	//FVector4 RotationZDegReturn(float _Angle)
	//{
	//	return RotationZRadReturn(_Angle * FMath::D2R);
	//}

	TVector4 RotationZRadReturn(float _Angle)
	{
		TVector4 Result = *this;
		Result.X = (X * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (X * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}

	float Dot(const TVector4& other) const
	{
		return X * other.X + Y * other.Y;
	}

	TVector4 operator*(float _Value) const
	{
		TVector4 Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		Result.Z = Z * _Value;
		return Result;
	}

	TVector4 operator/(float _Value) const
	{
		TVector4 Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		Result.Z = Z / _Value;
		return Result;
	}

	TVector4 operator+(const TVector4& _Other) const
	{
		TVector4 Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	TVector4 operator*(const class FMatrix& _Matrix) const;
	TVector4& operator*=(const class FMatrix& _Matrix);

	TVector4& operator-=(const TVector4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}


	TVector4 operator-(const TVector4& _Other) const
	{
		TVector4 Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	TVector4 operator-() const
	{
		TVector4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}



	TVector4 operator/(const TVector4& Other) const
	{
		TVector4 Result;
		Result.X = X / Other.X;
		Result.Y = Y / Other.Y;
		return Result;
	}

	// ture가 나오는 
	bool operator==(const TVector4& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float은 비교가 굉장히 위험
	// const가 붙은 함수에서는 const가 붙은 함수 호출할수 없다.
	bool EqualToInt(TVector4 _Other) const
	{
		// const FVector* const Ptr;
		// this = nullptr;
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	//bool Compare(FVector _Other, float _limite = 0.0f) const
	//{
	//	return X == _Other.X && Y == _Other.Y;
	//}

	TVector4& operator+=(const TVector4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;
		return *this;
	}

	TVector4& operator*=(const TVector4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;
		return *this;
	}

	TVector4& operator*=(float _Other)
	{
		X *= _Other;
		Y *= _Other;
		Z *= _Other;
		return *this;
	}
};

