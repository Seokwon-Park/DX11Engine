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

	//	// �Ʒ��� ���� ����°� �νŴ� ���������� ���մϴ�.
	//	/*Arr2D[1][1] = cosf(_Angle.X) * ;
	//	Arr2D[1][2] = -sinf(_Angle.X);
	//	Arr2D[2][1] = sinf(_Angle.X);
	//	Arr2D[2][2] = cosf(_Angle.X) * cosf(_Angle.Y);*/

	//	//RotX.RotationXDeg(_Angle.X);
	//	//RotY.RotationYDeg(_Angle.Y);
	//	//RotZ.RotationZDeg(_Angle.Z);

	//	// ������ �ٲ���� �Ҷ��� �ֽ��ϴ�.
	//	// �������̶�� ������ �߻��ϱ� ������
	//	// RotY * RotZ * RotX;
	//	*this = RotX * RotY * RotZ;
	//}



	//// View����� �����Դϴ�.
	//void View(const FVector4& _Pos, const FVector4& _Dir, const FVector4& _Up)
	//{
	//	// _Pos ī�޶� ��� �ٶ󺸰� �ֳ���?
	//	// _Dir ������� �ֳ���?
	//	// _Up �ٶ󺸴� ����� �������� �����ϴ� ���͸� �־��ּ���.

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

	//	// ���� ȸ����� ������?
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

	//// ���⼭ �޼� ���� �� ��ǥ�赵 �ٲܼ� �ֽ��ϴ�.

	//// _Widht �ʺ�� <= ������ ũ�� �ִ°� �Ϲ���
	//// _Height ���� ȭ����
	//// 
	//// �� �տ��ִ� _Far�Ÿ� �ȿ� �ִ� �ֵ���� ���ڴ�.
	//// �� �տ��ִ� _Near���� ���ڴ�. 

	////                 
	//void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	//{
	//	Identity();

	//	// 1000;
	//	// 250 * (2 / 1000);
	//	// ũ�⸦ �ٲٴ� ����̴� 
	//	// ������ ������ 

	//	//                      11      1      
	//	float fRange = 1.0f / (_Far - _Near);

	//	// [*][ ][ ][ ]
	//	// [ ][*][ ][ ]
	//	// [ ][ ][*][ ]
	//	// [ ][ ][*][ ]

	//	Arr2D[0][0] = 2.0f / _Width;
	//	Arr2D[1][1] = 2.0f / _Height;
	//	Arr2D[2][2] = fRange;

	//	// Camera�� z�� near�� ���̿� �ִ� ������� z -������ ������ ���ؼ� �̴�.
	//	// ū�ǹ̴� ����. ���ڰ� �ʹ� �۾�
	//	Arr2D[3][2] = -fRange * _Near;
	//	// �׸�ŭ ������ ���ܼ� ����Ϳ� �� �ٿ��ַ��� �ϴ°�.
	//	// ���� ������ -1~1������ ���� �ǰ� ����� �̴ٰϴ�.

	//}

	//// �������� �ϳ��� 

	//// ȭ���� ũ�⸦ �����ϱ� ���� _Width, _Height X
	//// ȭ���� ������ �����ϱ� ���� _Width, _Height O
	//// _FovAngle => x�࿡�� �ٶ�������� ������ �˷��޶�.
	////void PerspectiveFovDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	////{
	////	PerspectiveFovRad(_FovAngle * FMath::D2R, _Width, _Height, _Near, _Far);
	////}

	//void PerspectiveFovRad(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	//{
	//	Identity();

	//	float ScreenRatio = _Width / _Height;
	//	float DivFov = _FovAngle / 2.0f;

	//	// / z�� �ؾ��ϴϱ�.
	//	// / z�� �ϱ� �������� ���� ������ ���� �ִ�.

	//	Arr2D[2][3] = 1.0f;
	//	Arr2D[3][3] = 0.0f;

	//	// x * 1.0f / (tanf(DivFov) * ScreenRatio) / z
	//	Arr2D[0][0] = 1.0f / (tanf(DivFov) * ScreenRatio);
	//	// y * 1.0f / (tanf(DivFov) * ScreenRatio)
	//	Arr2D[1][1] = 1.0f / tanf(DivFov);
	//	// z���� 0, 1������ ������ ����� ���� �����̴�.
	//	// ���⿡�� z * �� �Ǵ� ���̴�.
	//	Arr2D[2][2] = _Far / (_Far - _Near);
	//	// 0~ 1������ ������ ������� �ֳ���?

	//	Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
	//}

	//// ȭ�� Ȯ�� -1~1������ ���� �����ϱ�
	//// +��ǥ�� ���� ���� ����
	//// ȭ���� ���߾��� 0,0���� ����ϴ�
	//// Y�� ������ ���⼭ �մϴ�.
	//// ����Ʈ�� directx������ ���� ������ �ʿ䰡 ����. ���̷��� �־��ָ� ���̷�Ʈ�� �ڵ����� ���ִ� ���̴�.
	//// directx::viewportsetting(ViewPort_desc);

	//// ��ġ�� ũ�� ���ʿ����� �ִ� ����̴�.
	//// �װ������� ��������� ���Ҽ� �־�.

	////                 1280          720        640           360            ���� �տ� ������ ���� �ڿ� ���ðų�
	//void ViewPort(float _Width, float _Height, float _Left, float _Top, float _ZMin, float _ZMax)
	//{
	//	Identity();
	//	Arr2D[0][0] = _Width * 0.5f;
	//	// Y�� ����
	//	Arr2D[1][1] = -_Height * 0.5f;

	//	// ȭ�� 2~3�Ѹ��ǵ� ���߿��� ���� �տ����� �ڿ����� �����Ϸ��� 
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
