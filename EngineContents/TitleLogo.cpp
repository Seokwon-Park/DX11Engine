#include "EnginePCH.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	SpriteRenderer = CreateDefaultSubobject<USpriteRendererComponent>();
	SpriteRenderer->SetSprite("Tevi", 99);
	SpriteRenderer->SetOrder(ESortingLayer::Default, -1);

	Collider = CreateDefaultSubobject<UBoxCollider2DComponent>();
	Collider->SetCollisionLayer(ECollisionLayer::Enemy);
	Collider->SetRelativeScale3D(FVector4(1000.0f,100.0f, 1.0f));

	SpriteRenderer->SetupAttachment(RootComponent);
	Collider->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//SetActorLocation({ 100.0f, 0.0f, 1.0f, 1.0f });
}
void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}
