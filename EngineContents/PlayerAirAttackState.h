#pragma once

// Ό³Έν :
class PlayerAirAttackState
{
public:
	// constrcuter destructer
	PlayerAirAttackState();
	~PlayerAirAttackState();

	// delete Function
	PlayerAirAttackState(const PlayerAirAttackState& _Other) = delete;
	PlayerAirAttackState(PlayerAirAttackState&& _Other) noexcept = delete;
	PlayerAirAttackState& operator=(const PlayerAirAttackState& _Other) = delete;
	PlayerAirAttackState& operator=(PlayerAirAttackState&& _Other) noexcept = delete;

protected:

private:

};

