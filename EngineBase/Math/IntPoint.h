#pragma once

class FIntPoint
{
public:
	union
	{
		struct
		{
			int X;
			int Y;
		};
		int V[2];
	};

	FIntPoint();
	FIntPoint(int _X, int _Y);

	FIntPoint operator+(const FIntPoint& _Other) const;
	FIntPoint operator-(const FIntPoint& _Other) const;
	void operator+=(const FIntPoint& _Other);
	void operator-=(const FIntPoint& _Other);

	inline FIntPoint operator/(int _Value) const
	{
		return FIntPoint(X / _Value, Y / _Value);
	}

	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;
};
