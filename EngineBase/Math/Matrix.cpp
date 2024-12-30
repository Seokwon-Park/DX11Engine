#include "EnginePCH.h"
#include "Matrix.h"

FMatrix::FMatrix()
{
	this->MatrixIdentity();
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
}

void FMatrix::MatrixRotationY(float _Radian)
{
}

void FMatrix::MatrixRotationZ(float _Radian)
{
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
	Mat = DirectX::XMMatrixPerspectiveFovLH(_Fov, _AspectRatio, _Near, _Far);
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
	DirectX::XMMATRIX Mat = DirectX::XMMatrixMultiply(this->Mat, _Mat.Mat);
	FMatrix Result;
	Result.Mat = Mat;
	return Result;
}






