#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATestGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATestGameMode();
	~ATestGameMode();

	// delete Function
	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

