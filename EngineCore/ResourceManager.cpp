#include "EnginePCH.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/Graphics/EngineTexture.h>

UResourceManager::UResourceManager()
{
}

UResourceManager::~UResourceManager()
{
}

std::shared_ptr<UEngineResource> UResourceManager::Find(std::string_view _ResourceType, std::string_view _ResourceName)
{
	std::string UpperString = UEngineString::ToUpper(_ResourceName);

	if (false == ResourceMap[_ResourceType.data()].contains(UpperString))
	{
		return nullptr;
	}

	return ResourceMap[_ResourceType.data()][UpperString];
}

void UResourceManager::LoadImages(std::vector<std::string> _Exts)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}
	Dir.Move("Image");
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].ToString();
		std::shared_ptr<UEngineTexture2D> Image = UEngineTexture2D::Create(FilePath);
		AddResource<UEngineTexture2D>(Image, ImageFiles[i].GetCurrentName(), FilePath);
	}
}

void UResourceManager::AddResource(std::shared_ptr<UEngineResource> _Resource, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
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