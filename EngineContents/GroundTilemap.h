#pragma once
#include <EngineCore/TilemapActor.h>

// Ό³Έν :
class AGroundTilemap : public ATilemapActor
{
public:
	// constrcuter destructer
	AGroundTilemap();
	~AGroundTilemap();

	// delete Function
	AGroundTilemap(const AGroundTilemap& _Other) = delete;
	AGroundTilemap(AGroundTilemap&& _Other) noexcept = delete;
	AGroundTilemap& operator=(const AGroundTilemap& _Other) = delete;
	AGroundTilemap& operator=(AGroundTilemap&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
};

