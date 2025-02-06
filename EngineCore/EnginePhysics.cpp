#include "EnginePCH.h"
#include "EnginePhysics.h"
#include "Level.h"

std::map<ECollisionLayer, unsigned long long> UEnginePhysics::CollisionRule;
ULevel* UEnginePhysics::CurLevel;

float RayCastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context)
{
	RayCastContext* myContext = reinterpret_cast<RayCastContext*>(context);
	myContext->shapeId = shapeId;
	myContext->point = point;
	myContext->normal = normal;
	myContext->fraction = fraction;
	return fraction;
}

float OverlapCallback(b2ShapeId shapeId, void* context)
{
	RayCastContext* myContext = reinterpret_cast<RayCastContext*>(context);
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

bool UEnginePhysics::RayCast(FVector4 _Position, FVector4 _Direction, float _Distance, ECollisionLayer _Layer)
{
	RayCastContext Context = { 0 };

	b2Vec2 Pos = b2Vec2(_Position.X / FMath::BOX2DSCALE, _Position.Y / FMath::BOX2DSCALE);
	b2QueryFilter Filter = b2DefaultQueryFilter();
	Filter.maskBits = _Layer;
	b2World_CastRay(CurLevel->GetPhysicsWorld(), Pos, b2Vec2(_Direction.X, _Direction.Y), Filter, RayCastCallback, &Context);
	b2Vec2 HitPoint = Context.point;
	b2Vec2 PlayerPoint = Pos;
	float Dist = b2Distance(HitPoint, PlayerPoint) * FMath::BOX2DSCALE;

	//std::cout << Context.shapeId.index1 << '\n';
	return Dist <= _Distance;
}

std::vector<UCollider2DComponent> UEnginePhysics::CircleCollider(FVector4 _Position, float _Radius, ECollisionLayer _Layer)
{
	b2Circle Circle;
	Circle.radius = 0;
	Circle.center = b2Vec2(_Position.X / FMath::BOX2DSCALE, _Position.Y / FMath::BOX2DSCALE);
	b2QueryFilter Filter = b2DefaultQueryFilter();
	b2World_OverlapCircle(CurLevel->GetPhysicsWorld(), &Circle, b2Transform_identity, Filter, OverlapCallback, &Context);
	return true;
}
