#include "EnginePCH.h"
#include "Level.h"
#include "Actor.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
}

void ULevel::Tick(float _DeltaTime)
{
<<<<<<< HEAD
=======
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	for (; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		/*if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}*/

		StartIter = BeginPlayList.erase(StartIter);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}

	// ���� Ranged for�ȿ����� erase ����Ʈ�� ������ ����� ���� ���� ����� �ߤ����.
	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		CurActor->Tick(_DeltaTime);
	}
>>>>>>> e303e6160b12585f4d905ed7f018109223275f16
}