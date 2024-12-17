#pragma once

#include "Actor.h"

// 클래스 설명 :
class APawn :public AActor
{
public:
	// Constrcuter Destructer
	ENGINE_API APawn();
	ENGINE_API ~APawn();

	// Delete Function
	APawn(const APawn& _Other) = delete;
	APawn(APawn&& _Other) noexcept = delete;
	APawn& operator=(const APawn& _Other) = delete;
	APawn& operator=(APawn&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:

};
