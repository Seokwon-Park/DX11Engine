#pragma once

#include "Vector4.h"

#include <DirectXMath.h>

//float4x4 Matrix
class BASE_API FMatrix
{
public:
	union
	{
		float Array2D[4][4];
		float Array1D[16];
		FVector4 Rows[4];
		DirectX::XMMATRIX Mat;

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
	};

	FMatrix();

	void MatrixIdentity();
	void MatrixTranspose();

	void MatrixScaling(FVector4 _Scale);
	void MatrixRotation(FVector4 _Rotation);
	void MatrixRotationX(float _Radian);
	void MatrixRotationY(float _Radian);
	void MatrixRotationZ(float _Radian);
	void MatrixTranslation(FVector4 _Translate);

	static inline friend std::ostream& operator<<(std::ostream& _Ostream, const FMatrix& _Matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_Ostream << _Matrix.Array2D[i][j] << ' ';
			}
			_Ostream << '\n';
		}
		return _Ostream;
	}
	//FVector4 GetFoward()
	//{
	//	FVector4 Dir = ArrVector[2];
	//	Dir.Normalize();
	//	return Dir;
	//}

	//FVector4 GetRight()
	//{
	//	FVector4 Dir = ArrVector[0];
	//	Dir.Normalize();
	//	return Dir;
	//}

	//FVector4 GetUp()
	//{
	//	FVector4 Dir = ArrVector[1];
	//	Dir.Normalize();
	//	return Dir;
	//}

	//FMatrix operator*(const FMatrix& _Value);

	//void Scale(const FVector4& _Value)
	//{
	//	Arr2D[0][0] = _Value.X;
	//	Arr2D[1][1] = _Value.Y;
	//	Arr2D[2][2] = _Value.Z;
	//}

	//void Position(const FVector4& _Value)
	//{
	//	Arr2D[3][0] = _Value.X;
	//	Arr2D[3][1] = _Value.Y;
	//	Arr2D[3][2] = _Value.Z;
	//}

	//void RotationDeg(const FVector4& _Angle)
	//{
	//	FMatrix RotX;
	//	FMatrix RotY;
	//	FMatrix RotZ;

	//	// 아래와 같이 만드는게 훨신더 빠르겠지만 안합니다.
	//	/*Arr2D[1][1] = cosf(_Angle.X) * ;
	//	Arr2D[1][2] = -sinf(_Angle.X);
	//	Arr2D[2][1] = sinf(_Angle.X);
	//	Arr2D[2][2] = cosf(_Angle.X) * cosf(_Angle.Y);*/

	//	//RotX.RotationXDeg(_Angle.X);
	//	//RotY.RotationYDeg(_Angle.Y);
	//	//RotZ.RotationZDeg(_Angle.Z);

	//	// 순서를 바꿔줘야 할때가 있습니다.
	//	// 짐벌락이라는 현상이 발생하기 때문에
	//	// RotY * RotZ * RotX;
	//	*this = RotX * RotY * RotZ;
	//}



	//// View행렬의 인자입니다.
	//void View(const FVector4& _Pos, const FVector4& _Dir, const FVector4& _Up)
	//{
	//	// _Pos 카메라가 어디서 바라보고 있나요?
	//	// _Dir 어딜보고 있나요?
	//	// _Up 바라보는 방향과 수직으로 직교하는 벡터를 넣어주세요.

	//	// -90
	//	FVector4 Forward = _Dir.NormalizeReturn();
	//	FVector4 Up = _Up.NormalizeReturn();
	//	FVector4 Right = FVector4::Cross(Up, Forward);
	//	Right.Normalize();


	//	ArrVector[2] = Forward;
	//	ArrVector[1] = Up;
	//	ArrVector[0] = Right;

	//	ArrVector[2].W = 0.0f;
	//	ArrVector[1].W = 0.0f;
	//	ArrVector[0].W = 0.0f;

	//	// 나의 회전행렬 구했죠?
	//	// 90 
	//	Transpose();

	//	FMatrix OrginRot = *this;

	//	FVector4 NPos = -_Pos;

	//	ArrVector[3].X = FVector4::Dot(Right, NPos);
	//	ArrVector[3].Y = FVector4::Dot(Up, NPos);
	//	ArrVector[3].Z = FVector4::Dot(Forward, NPos);

	//	FVector4 Move = ArrVector[3];
	//	FVector4 OriginMove = NPos * OrginRot;

	//	return;
	//}

	//// 여기서 왼손 오른 손 좌표계도 바꿀수 있습니다.

	//// _Widht 너비와 <= 윈도우 크기 넣는게 일반적
	//// _Height 높의 화면을
	//// 
	//// 내 앞에있는 _Far거리 안에 있는 애들까지 보겠다.
	//// 내 앞에있는 _Near부터 보겠다. 

	////                 
	//void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	//{
	//	Identity();

	//	// 1000;
	//	// 250 * (2 / 1000);
	//	// 크기를 바꾸는 행렬이다 
	//	// 직교는 더더욱 

	//	//                      11      1      
	//	float fRange = 1.0f / (_Far - _Near);

	//	// [*][ ][ ][ ]
	//	// [ ][*][ ][ ]
	//	// [ ][ ][*][ ]
	//	// [ ][ ][*][ ]

	//	Arr2D[0][0] = 2.0f / _Width;
	//	Arr2D[1][1] = 2.0f / _Height;
	//	Arr2D[2][2] = fRange;

	//	// Camera의 z와 near와 사이에 있는 존재들을 z -축으로 보내기 위해서 이다.
	//	// 큰의미는 없다. 숫자가 너무 작어
	//	Arr2D[3][2] = -fRange * _Near;
	//	// 그만큼 앞으로 땡겨서 모니터에 딱 붙여주려고 하는것.
	//	// 직교 투영은 -1~1사이의 값이 되게 만들어 줄겁니다.

	//}

	//// 인자중의 하나는 

	//// 화면의 크기를 정의하기 위한 _Width, _Height X
	//// 화면의 비율을 정의하기 위한 _Width, _Height O
	//// _FovAngle => x축에서 바라봤을대의 각도를 알려달라.
	////void PerspectiveFovDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	////{
	////	PerspectiveFovRad(_FovAngle * FMath::D2R, _Width, _Height, _Near, _Far);
	////}

	//void PerspectiveFovRad(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	//{
	//	Identity();

	//	float ScreenRatio = _Width / _Height;
	//	float DivFov = _FovAngle / 2.0f;

	//	// / z를 해야하니까.
	//	// / z를 하기 전까지의 값은 추출해 낼수 있다.

	//	Arr2D[2][3] = 1.0f;
	//	Arr2D[3][3] = 0.0f;

	//	// x * 1.0f / (tanf(DivFov) * ScreenRatio) / z
	//	Arr2D[0][0] = 1.0f / (tanf(DivFov) * ScreenRatio);
	//	// y * 1.0f / (tanf(DivFov) * ScreenRatio)
	//	Arr2D[1][1] = 1.0f / tanf(DivFov);
	//	// z값을 0, 1사이의 값으로 만드는 것이 목적이다.
	//	// 여기에서 z * 가 되는 값이다.
	//	Arr2D[2][2] = _Far / (_Far - _Near);
	//	// 0~ 1사이의 값으로 만들수가 있나요?

	//	Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
	//}

	//// 화면 확대 -1~1사이의 값이 됐으니까
	//// +좌표축 변경 중점 변경
	//// 화면의 정중앙을 0,0으로 만듭니다
	//// Y축 반전도 여기서 합니다.
	//// 뷰포트는 directx에서는 내가 곱해줄 필요가 없다. 다이렉에 넣어주면 다이렉트가 자동으로 해주는 것이다.
	//// directx::viewportsetting(ViewPort_desc);

	//// 위치와 크기 양쪽영향을 주는 행렬이다.
	//// 그것조차도 내마음대로 정할수 있어.

	////                 1280          720        640           360            누가 앞에 나오고 누가 뒤에 나올거냐
	//void ViewPort(float _Width, float _Height, float _Left, float _Top, float _ZMin, float _ZMax)
	//{
	//	Identity();
	//	Arr2D[0][0] = _Width * 0.5f;
	//	// Y축 반전
	//	Arr2D[1][1] = -_Height * 0.5f;

	//	// 화면 2~3뿌릴건데 그중에서 누가 앞에오고 뒤에오고를 결정하려면 
	//	Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

	//	Arr2D[3][0] = Arr2D[0][0] + _Left;
	//	Arr2D[3][1] = -Arr2D[1][1] + _Top;
	//	Arr2D[3][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;
	//}


	////void RotationXDeg(float _Angle)
	////{
	////	RotationXRad(_Angle * FMath::D2R);
	////}

	////void RotationXRad(float _Angle)
	////{
	////	Identity();
	////	Arr2D[1][1] = cosf(_Angle);
	////	Arr2D[1][2] = -sinf(_Angle);
	////	Arr2D[2][1] = sinf(_Angle);
	////	Arr2D[2][2] = cosf(_Angle);
	////}

	////void RotationYDeg(float _Angle)
	////{
	////	RotationYRad(_Angle * FMath::D2R);
	////}

	////void RotationYRad(float _Angle)
	////{
	////	Identity();
	////	Arr2D[0][0] = cosf(_Angle);
	////	Arr2D[0][2] = sinf(_Angle);
	////	Arr2D[2][0] = -sinf(_Angle);
	////	Arr2D[2][2] = cosf(_Angle);
	////}

	////void RotationZDeg(float _Angle)
	////{
	////	RotationZRad(_Angle * FMath::D2R);
	////}

	////void RotationZRad(float _Angle)
	////{
	////	Identity();
	////	Arr2D[0][0] = cosf(_Angle);
	////	Arr2D[0][1] = -sinf(_Angle);
	////	Arr2D[1][0] = sinf(_Angle);
	////	Arr2D[1][1] = cosf(_Angle);
	////}

};
