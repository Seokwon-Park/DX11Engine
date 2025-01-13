#include "EnginePCH.h"
#include "Matrix.h"

FMatrix::FMatrix()
{
	this->MatrixIdentity();
}

FMatrix FMatrix::Transpose(const FMatrix& _Matrix)
{
	FMatrix Result = _Matrix;
	Result.MatrixTranspose();
	return Result;
}

void FMatrix::MatrixInverse()
{
	Mat = DirectX::XMMatrixInverse(nullptr, Mat);
}

void FMatrix::MatrixIdentity()
{
	Mat = DirectX::XMMatrixIdentity();
}

void FMatrix::MatrixTranspose()
{
	Mat = DirectX::XMMatrixTranspose(Mat);
}


void FMatrix::MatrixScaling(FVector4 _Scale)
{
	DirectX::XMVECTOR Vec = DirectX::XMLoadFloat4A(&_Scale.XMFloat);
	Mat = DirectX::XMMatrixScalingFromVector(Vec);
}

void FMatrix::MatrixRotation(FVector4 _Rotation)
{
	DirectX::XMVECTOR Vec = DirectX::XMLoadFloat4A(&_Rotation.XMFloat);
	Mat = DirectX::XMMatrixRotationRollPitchYawFromVector(Vec);
}

void FMatrix::MatrixRotationX(float _Radian)
{
	Mat = DirectX::XMMatrixRotationX(_Radian);
}

void FMatrix::MatrixRotationY(float _Radian)
{
	Mat = DirectX::XMMatrixRotationY(_Radian);
}

void FMatrix::MatrixRotationZ(float _Radian)
{
	Mat = DirectX::XMMatrixRotationZ(_Radian);
}

void FMatrix::MatrixTranslation(FVector4 _Translate)
{
	DirectX::XMVECTOR Vec = DirectX::XMLoadFloat4A(&_Translate.XMFloat);
	Mat = DirectX::XMMatrixTranslationFromVector(Vec);
}

void FMatrix::MatrixView(FVector4 _ViewPos, FVector4 _ViewDir, FVector4 _UpDir)
{
	DirectX::XMVECTOR ViewPos = DirectX::XMLoadFloat4A(&_ViewPos.XMFloat);
	DirectX::XMVECTOR ViewDir = DirectX::XMLoadFloat4A(&_ViewDir.XMFloat);
	DirectX::XMVECTOR UpDir = DirectX::XMLoadFloat4A(&_UpDir.XMFloat);

	Mat = DirectX::XMMatrixLookToLH(ViewPos, ViewDir, UpDir);
}

void FMatrix::MatrixPerspectiveProj(float _Width, float _Height, float _Near, float _Far)
{
	Mat = DirectX::XMMatrixPerspectiveLH(_Width, _Height, _Near, _Far);
}

void FMatrix::MatrixPerspectiveFov(float _Fov, float _AspectRatio, float _Near, float _Far)
{
	Mat = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(_Fov), _AspectRatio, _Near, _Far);
}

void FMatrix::MatrixOrthoFovLH(float _Fov, float _AspectRatio, float _Near, float _Far)
{
	MatrixIdentity();
	Mat = DirectX::XMMatrixOrthographicOffCenterLH(-_AspectRatio, _AspectRatio, -1.0f, 1.0f, _Near, _Far);
}

void FMatrix::MatrixOrthoLH(float _Width, float _Height, float _Near, float _Far)
{
	MatrixIdentity();
	Mat = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
}

FMatrix FMatrix::operator*(FMatrix _Mat)
{
	DirectX::XMMATRIX XMMat = DirectX::XMMatrixMultiply(Mat, _Mat.Mat);
	FMatrix Result;
	Result.Mat = XMMat;
	return Result;
}

FVector4 FMatrix::operator*(FVector4 _Vec4)
{
	DirectX::XMVECTOR XMVector = DirectX::XMVector3Transform(DirectX::XMLoadFloat4A(&_Vec4.XMFloat), Mat);
	FVector4 Result;
	DirectX::XMStoreFloat4A(&Result.XMFloat, XMVector);
	return Result;
}






