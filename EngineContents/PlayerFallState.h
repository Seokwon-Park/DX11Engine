#pragma once

// Ό³Έν :
class PlayerFallState
{
public:
	// constrcuter destructer
	PlayerFallState();
	~PlayerFallState();

	// delete Function
	PlayerFallState(const PlayerFallState& _Other) = delete;
	PlayerFallState(PlayerFallState&& _Other) noexcept = delete;
	PlayerFallState& operator=(const PlayerFallState& _Other) = delete;
	PlayerFallState& operator=(PlayerFallState&& _Other) noexcept = delete;

protected:

private:

};

