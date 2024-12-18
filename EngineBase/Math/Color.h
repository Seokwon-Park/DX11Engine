#pragma once

#include "EngineBase.h"

class ENGINE_API FColor
{
public:
	union
	{
		float V[4];
		struct
		{
			float R;
			float G;
			float B;
			float A;
		};
	};

	FColor();
	FColor(float _R, float _G, float _B, float _A);
		

	const static FColor WHITE;
	const static FColor BLACK;
	const static FColor RED;
	const static FColor GREEN;
	const static FColor BLUE;

	//bool operator==(const FColor& _Other)
	//{
	//	return R == _Other.R && G == _Other.G && B == _Other.B;
	//}
};


