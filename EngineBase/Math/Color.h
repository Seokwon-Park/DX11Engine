#pragma once

class FColor
{
public:
	static const FColor WHITE;
	static const FColor BLACK;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	FColor(unsigned long _Value);
	FColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A){}

	bool operator==(const FColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}
};


