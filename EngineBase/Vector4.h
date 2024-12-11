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

		// Cos�� �����ΰ���?
		// cos(����) => CosRad
		// cos(����)
		float CosRad = Dot(LCopy, RCopy);

		// cos �� ���Լ� 
		// cos(����) => ���
		// acos(���) => ����
		// cos�Լ��� ���Լ�
		return acos(CosRad);
	}

	//// 360�� �������� �־����.
	//static FVector4 AngleToVectorDeg(float _Angle)
	//{
	//	// 360�й��� => �������� �ٲٴ� ���� ������ �Ѵ�.
	//	// 360 => 6.28

	//	// ���� ����ü�踦 ������� sinf(_Angle) cosf

	//	// �ٺ��Լ��� ���� �������� �����
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

	//          Rad ������ �־��ָ� 
	// ���⿡�� ���� ������� �������ټ� �ִ°�
	// ���̰� 1�� �����̴�.
	// static�Դϱ�?
	static FVector4 AngleToVectorRad(float _Angle)
	{
		// Ư�� ������ ����Ű�� ���͸� ����� �ִٰ� ����?
		// ���� ���̿� ������ �����ض�.
		// ������ �������µ� ���̴� 1�� ���͸� ������ �̴ϴ�.

		// 0���϶��� �غ�      0���ϴ��� ����

		// cosf(_Angle) = �غ�
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

	// ������ �����Դϴ�.
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

	// ture�� ������ 
	bool operator==(const FVector4& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float�� �񱳰� ������ ����
	// const�� ���� �Լ������� const�� ���� �Լ� ȣ���Ҽ� ����.
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

