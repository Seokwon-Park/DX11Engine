#pragma once

class FColor
{
public:
	//static const FColor WHITE;
	//static const FColor BLACK;

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

	FColor(float _R, float _G, float _B, float _A);
		

	//bool operator==(const FColor& _Other)
	//{
	//	return R == _Other.R && G == _Other.G && B == _Other.B;
	//}
};


