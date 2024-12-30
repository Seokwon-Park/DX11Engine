#pragma once
#include <EngineCore/Pawn.h>
#include <EngineCore/Components/SpriteRendererComponent.h>
#include <EngineCore/Components/InputComponent.h>

// Ό³Έν :
class APlayer : public APawn
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	void TestFn();
protected:
	virtual void BeginPlay() override;

private:
	std::shared_ptr<USpriteRendererComponent> Test;
	std::shared_ptr<UInputComponent> Input;
};

