#pragma once
#include <random>	

// Ό³Έν :
class FRandom
{
public:
	// constrcuter destructer
	FRandom();
	~FRandom();

	// delete Function
	FRandom(const FRandom& _Other) = delete;
	FRandom(FRandom&& _Other) noexcept = delete;
	FRandom& operator=(const FRandom& _Other) = delete;
	FRandom& operator=(FRandom&& _Other) noexcept = delete;

	int GenerateRandomInt(int _InclusiveMin, int _InclusiveMax);
	float GenerateRandomFloat(float _InclusiveMin, float _InclusiveMax);

protected:

private:
	static std::mt19937_64 MTGenerator;
};

