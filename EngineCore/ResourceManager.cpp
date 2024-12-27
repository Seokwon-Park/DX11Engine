#include "EnginePCH.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>

UResourceManager::UResourceManager()
{
}

UResourceManager::~UResourceManager()
{
}

std::shared_ptr<UEngineResource> UResourceManager::Find(std::string_view _ResourceType, std::string_view _ResourceName)
{
	if (false == ResourceMap[_ResourceType.data()].contains(_ResourceName.data()))
	{
		return nullptr;
	}

	return ResourceMap[_ResourceType.data()][_ResourceName.data()];
}

void UResourceManager::PushRes(std::shared_ptr<UEngineResource> _Resource, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	if (true == ResourceMap[_Info.data()].contains(_Name.data()))
	{
		MSGASSERT("이미 로드한 리소스를 또 로드 하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_Name);

	_Resource->SetName(UpperName);
	_Resource->SetPath(_Path);
	ResourceMap[_Info.data()].insert(std::make_pair(UpperName, _Resource));

	return;
}