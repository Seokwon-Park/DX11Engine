#include "EnginePCH.h"
#include "Matrix.h"

FMatrix::FMatrix()
{
	this->MatrixIdentity();
}

void FMatrix::MatrixIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Array2D[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
}

void FMatrix::MatrixTranspose()
{
	for (size_t y = 0; y < 4; y++)
	{
		for (size_t x = y; x < 4; x++)
		{
			float Swap = Array2D[y][x];
			Array2D[y][x] = Array2D[x][y];
			Array2D[x][y] = Swap;
		}
	}
}

void FMatrix::MatrixScaling()
{

}

void FMatrix::MatrixRotationX()
{
}

void FMatrix::MatrixRotationY()
{
}

void FMatrix::MatrixRotationZ()
{
}

void FMatrix::MatrixTranslation()
{
}

