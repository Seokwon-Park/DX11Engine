#include "EnginePCH.h"
#include "Enemy.h"

AEnemy::AEnemy()
{
}

AEnemy::~AEnemy()
{
}

void AEnemy::BeginPlay()
{
	AEntity::BeginPlay();
}

void AEnemy::Tick(float _DeltaTime)
{
	AEntity::Tick(_DeltaTime);
}
