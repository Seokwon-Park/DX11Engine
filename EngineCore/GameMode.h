#pragma once

#include "Actor.h"

// ���� :
class AGameMode : public AActor
{
public:
	// constrcuter destructer
	ENGINE_API AGameMode();
	ENGINE_API virtual ~AGameMode();

	// delete Function
	AGameMode(const AGameMode& _Other) = delete;
	AGameMode(AGameMode&& _Other) noexcept = delete;
	AGameMode& operator=(const AGameMode& _Other) = delete;
	AGameMode& operator=(AGameMode&& _Other) noexcept = delete;
	
protected:

private:

};

