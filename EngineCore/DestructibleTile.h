#pragma once
#include "Actor.h"
#include <EngineCore/Components/Collider2DComponent.h>

// Ό³Έν :
class ADestructibleTile 
{
public:
	// constrcuter destructer
	ADestructibleTile(FVector4 _Pos, ULevel* _Level);
	~ADestructibleTile();

	// delete Function
	ADestructibleTile(const ADestructibleTile& _Other) = delete;
	ADestructibleTile(ADestructibleTile&& _Other) noexcept = delete;
	ADestructibleTile& operator=(const ADestructibleTile& _Other) = delete;
	ADestructibleTile& operator=(ADestructibleTile&& _Other) noexcept = delete;

	bool CheckPlayer();
	void Release();
	FVector4 GetPos() { return Pos; }
protected:

private:
	class ULevel* Level;

	b2ChainId myChainId;
	b2BodyId BodyId;
	FVector4 Pos;
	float Timer = 0.0f;

};

