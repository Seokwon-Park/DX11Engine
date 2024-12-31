#include "EnginePCH.h"
#include "Vector2.h"

FVector2::FVector2()
	:X(0.0f), Y(0.0f)
{

}
FVector2::FVector2(int _X, int _Y)
	:X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
{

}
FVector2::FVector2(float _X, float _Y)
	:X(_X), Y(_Y)
{

}

std::ostream& operator<<(std::ostream& _Ostream, const FVector2& _Vector)
{
	// TODO: 여기에 return 문을 삽입합니다.
}
