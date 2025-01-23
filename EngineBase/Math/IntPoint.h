#pragma once

class BASE_API FIntPoint
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

	static friend std::ostream& operator<<(std::ostream& _Ostream, const FIntPoint& _Point)
	{
		_Ostream << "(" << _Point.X << ", " << _Point.Y << ")";
		return _Ostream;
	}

	FIntPoint operator+(const FIntPoint& _Other) const;
	FIntPoint operator-(const FIntPoint& _Other) const;
	FIntPoint operator/(const FIntPoint& _Other) const;
	FIntPoint operator/(int _Value) const;
	void operator+=(const FIntPoint& _Other);
	void operator-=(const FIntPoint& _Other);
	

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
