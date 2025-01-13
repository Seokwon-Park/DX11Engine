#include "EnginePCH.h"
#include "Random.h"

std::mt19937_64 FRandom::MTGenerator = std::mt19937_64(time(nullptr));

FRandom::FRandom()
{
}

FRandom::~FRandom()
{
}

int FRandom::GenerateRandomInt(int _InclusiveMin, int _InclusiveMax)
{
	if (_InclusiveMin >= _InclusiveMax)
	{
		return 0;
	}

	std::uniform_int_distribution<int> RandomInt(_InclusiveMin, _InclusiveMax);

	return RandomInt(MTGenerator);
}

float FRandom::GenerateRandomFloat(float _InclusiveMin, float _InclusiveMax)
{
	if (_InclusiveMin >= _InclusiveMax)
	{
		return 0.0f;
	}

	std::uniform_real_distribution<float> RandomFloat(_InclusiveMin, _InclusiveMax);

	return RandomFloat(MTGenerator);
}