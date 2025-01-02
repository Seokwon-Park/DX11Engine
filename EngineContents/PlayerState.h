#pragma once
#include "BaseState.h"
#include "Player.h"

// Ό³Έν :
class PlayerState : public BaseState
{
public:
	// constrcuter destructer
	PlayerState();
	~PlayerState();

	// delete Function
	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(PlayerState&& _Other) noexcept = delete;

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

protected:
	APlayer* Player;
	
private:

};

