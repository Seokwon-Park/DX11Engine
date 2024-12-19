#include "EnginePCH.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	Test = CreateDefaultSubObject<URendererComponent>();
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();


}
