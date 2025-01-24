#include "EnginePCH.h"
#include "EnginePhysics.h"
#include "Level.h"

std::map<ECollisionLayer, unsigned long long> UEnginePhysics::CollisionRule;

float RayCastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context)
{
	RayCastContext* myContext = (RayCastContext*)context;
	myContext->shapeId = shapeId;
	myContext->point = point;
	myContext->normal = normal;
	myContext->fraction = fraction;
	return fraction;
}

UEnginePhysics::UEnginePhysics()
{
}

UEnginePhysics::~UEnginePhysics()
{
}

bool UEnginePhysics::RayCast(ULevel* _Level, FVector4 _Position, FVector4 _Direction, float _Distance, ECollisionLayer _Layer)
{
	RayCastContext Context = { 0 };

	b2Vec2 PlayerPos = b2Vec2(_Position.X / FMath::BOX2DSCALE, _Position.Y / FMath::BOX2DSCALE);
	b2QueryFilter Filter = b2DefaultQueryFilter();
	Filter.maskBits = _Layer;
	b2World_CastRay(_Level->GetPhysicsWorld(), PlayerPos, b2Vec2(_Direction.X, _Direction.Y), Filter, RayCastCallback, &Context);
	b2Vec2 HitPoint = Context.point;
	b2Vec2 PlayerPoint = PlayerPos;
	float Dist = b2Distance(HitPoint, PlayerPoint) * FMath::BOX2DSCALE;
	std::cout << Context.shapeId.index1 << '\n';
	return Dist <= _Distance;
}
