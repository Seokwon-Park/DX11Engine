#pragma once


struct FVector4
{
	static const FVector4 ZERO;
	static const FVector4 LEFT;
	static const FVector4 RIGHT;
	static const FVector4 UP;
	static const FVector4 DOWN;
	static const FVector4 FORWARD;
	static const FVector4 BACK;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float XYZW[4];
	};


	FVector4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	FVector4(float _X, float _Y) : X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{

	}

	FVector4(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	FVector4(float _X, float _Y, float _Z, float _W) : X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

	FVector4(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	FVector4(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	static float Dot(const FVector4& _Left, const FVector4& _Right);
	static FVector4 Cross(const FVector4& _Left, const FVector4& _Right);
	static FVector4 Normalize(FVector4 _Value);

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

	static float GetVectorAngleDeg(const FVector4& _Left, const FVector4& _Right)
	{
		//return GetVectorAngleRad(_Left, _Right) * FMath::R2D;
	}


	static float GetVectorAngleRad(const FVector4& _Left, const FVector4& _Right)
	{
		FVector4 LCopy = _Left;
		FVector4 RCopy = _Right;
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


	static FVector4 Lerp(FVector4 _A, FVector4 _B, float _Alpha)
	{
		FVector4 Result;
		_Alpha = FMath::Clamp(_Alpha, 0.0f, 1.0f);
		Result.X = FMath::Lerp(_A.X, _B.X, _Alpha);
		Result.Y = FMath::Lerp(_A.Y, _B.Y, _Alpha);
		return Result;
	}

	//          Rad 라디안을 넣어주면 
	// 여기에서 나온 결과값이 리턴해줄수 있는건
	// 길이가 1인 벡터이다.
	// static입니까?
	static FVector4 AngleToVectorRad(float _Angle)
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

	FVector4 Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	// 빗변의 길이입니다.
	float Length() const
	{
		return FMath::Sqrt(X * X + Y * Y + Z * Z);
	}

	FVector4 NormalizeReturn() const
	{
		FVector4 Result = *this;
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

	FVector4 RotationZRadReturn(float _Angle)
	{
		FVector4 Result = *this;
		Result.X = (X * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (X * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}

	float Dot(const FVector4& other) const
	{
		return X * other.X + Y * other.Y;
	}

	FVector4 operator*(float _Value) const
	{
		FVector4 Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		Result.Z = Z * _Value;
		return Result;
	}

	FVector4 operator/(float _Value) const
	{
		FVector4 Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		Result.Z = Z / _Value;
		return Result;
	}

	FVector4 operator+(const FVector4& _Other) const
	{
		FVector4 Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector4 operator*(const class FMatrix& _Matrix) const;
	FVector4& operator*=(const class FMatrix& _Matrix);

	FVector4& operator-=(const FVector4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}


	FVector4 operator-(const FVector4& _Other) const
	{
		FVector4 Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FVector4 operator-() const
	{
		FVector4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}



	FVector4 operator/(const FVector4& Other) const
	{
		FVector4 Result;
		Result.X = X / Other.X;
		Result.Y = Y / Other.Y;
		return Result;
	}

	// ture가 나오는 
	bool operator==(const FVector4& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float은 비교가 굉장히 위험
	// const가 붙은 함수에서는 const가 붙은 함수 호출할수 없다.
	bool EqualToInt(FVector4 _Other) const
	{
		// const FVector* const Ptr;
		// this = nullptr;
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	//bool Compare(FVector _Other, float _limite = 0.0f) const
	//{
	//	return X == _Other.X && Y == _Other.Y;
	//}

	FVector4& operator+=(const FVector4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;
		return *this;
	}

	FVector4& operator*=(const FVector4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;
		return *this;
	}

	FVector4& operator*=(float _Other)
	{
		X *= _Other;
		Y *= _Other;
		Z *= _Other;
		return *this;
	}
};

