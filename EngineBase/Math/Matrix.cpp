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
	this->Mat = DirectX::XMMatrixScalingFromVector(Vec);
}

void FMatrix::MatrixRotation(FVector4 _Rotation)
{
	DirectX::XMVECTOR Vec = DirectX::XMLoadFloat4A(&_Rotation.XMFloat);
	this->Mat = DirectX::XMMatrixRotationRollPitchYawFromVector(Vec);
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
	this->Mat = DirectX::XMMatrixTranslationFromVector(Vec);
}


