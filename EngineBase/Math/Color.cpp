#include "EnginePCH.h"
#include "Color.h"


const FColor FColor::WHITE = FColor(1.0f, 1.0f, 1.0f, 1.0f);
const FColor FColor::BLACK = FColor(0.0f, 0.0f, 0.0f, 1.0f);
const FColor FColor::RED = FColor(1.0f, 0.0f, 0.0f, 1.0f);
const FColor FColor::GREEN = FColor(0.0f, 1.0f, 0.0f, 1.0f);
const FColor FColor::BLUE = FColor(0.0f, 0.0f, 1.0f, 1.0f);

FColor::FColor()
	:R(0.0f), G(0.0f), B(0.0f), A(0.0f) 
{
}

FColor::FColor(float _R, float _G, float _B, float _A)
	:R(_R), G(_G), B(_B), A(_A) {}
