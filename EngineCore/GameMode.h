#pragma once
#include "Actor.h"

// ���� :
class AGameMode : public AActor
{
public:
	// constrcuter destructer
	AGameMode();
	~AGameMode();

	// delete Function
	AGameMode(const AGameMode& _Other) = delete;
	AGameMode(AGameMode&& _Other) noexcept = delete;
	AGameMode& operator=(const AGameMode& _Other) = delete;
	AGameMode& operator=(AGameMode&& _Other) noexcept = delete;
	
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

