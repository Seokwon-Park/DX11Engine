#include "EnginePCH.h"
#include "DestructibleTile.h"
#include "EnginePhysics.h"

ADestructibleTile::ADestructibleTile(FVector4 _Pos, ULevel* _Level)
{
	Level = _Level;
	Pos = _Pos;
	float HalfWidth = 14.0f;
	float HalfHeight = 14.0f;

	b2Polygon dynamicBox = b2MakeBox(HalfWidth / FMath::BOX2DSCALE, HalfHeight / FMath::BOX2DSCALE);
	b2Vec2 P1 = dynamicBox.vertices[2];
	b2Vec2 P2 = dynamicBox.vertices[3];
	b2Transform Trans({ Pos.X / FMath::BOX2DSCALE, Pos.Y / FMath::BOX2DSCALE }, { 1.0f, 0.0f });// cos 0, sin 0
	P1 = b2TransformPoint(Trans, P1);
	P2 = b2TransformPoint(Trans, P2);

	std::vector<b2Vec2> points;

	points.push_back(P1);
	points.push_back(P1);
	points.push_back(P2);
	points.push_back(P2);

	b2ChainDef ChainDef = b2DefaultChainDef();
	ChainDef.points = points.data();
	ChainDef.count = static_cast<int32_t>(points.size());
	ChainDef.friction = 0.0f;
	ChainDef.filter.categoryBits = ECollisionLayer::Ground;
	ChainDef.filter.maskBits = UEnginePhysics::CollisionRule[Ground];
	ChainDef.userData = this;

	b2BodyDef BD = b2DefaultBodyDef();
	BodyId = b2CreateBody(Level->GetPhysicsWorld(), &BD);
	myChainId = b2CreateChain(BodyId, &ChainDef);
}

ADestructibleTile::~ADestructibleTile()
{
}



bool ADestructibleTile::CheckPlayer()
{
	b2ContactEvents contactEvents = b2World_GetContactEvents(Level->GetPhysicsWorld());

	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
		auto A = b2Shape_GetUserData(beginEvent->shapeIdA);
		auto B = b2Shape_GetUserData(beginEvent->shapeIdB);
		if (A == Level->GetMainPawn<AActor>().get() && B == this)
		{
			return true;
		}
		else if (B == Level->GetMainPawn<AActor>().get() && A == this)
		{
			return true;
		}
	}
	return false;
}

void ADestructibleTile::Release()
{
	b2DestroyChain(myChainId);
	b2DestroyBody(BodyId);

}


