#include "EnginePCH.h"
#include "Vector4.h"



const TVector4 TVector4::ZERO = { 0.0f, 0.0f,0.0f };
const TVector4 TVector4::LEFT = { -1.0f, 0.0f,0.0f };
const TVector4 TVector4::RIGHT = { 1.0f, 0.0f, 0.0f };
const TVector4 TVector4::UP = { 0.0f, 1.0f, 0.0f };
const TVector4 TVector4::DOWN = { 0.0f, -1.0f, 0.0f };
const TVector4 TVector4::FORWARD = { 0.0f, 0.0f, 1.0f };
const TVector4 TVector4::BACK = { 0.0f, 0.0f , -1.0f };






TVector4 TVector4::Normalize(TVector4 _Value)
{
	_Value.Normalize();
	return _Value;
}