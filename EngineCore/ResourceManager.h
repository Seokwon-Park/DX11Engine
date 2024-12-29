#pragma once
#include "EngineResource.h"

// 설명 :
class UResourceManager
{
public:
	// constrcuter destructer
	UResourceManager();
	~UResourceManager();

	// delete Function
	UResourceManager(const UResourceManager& _Other) = delete;
	UResourceManager(UResourceManager&& _Other) noexcept = delete;
	UResourceManager& operator=(const UResourceManager& _Other) = delete;
	UResourceManager& operator=(UResourceManager&& _Other) noexcept = delete;

	template<typename ResourceType>
	static std::shared_ptr<ResourceType> Find(std::string_view _Name)
	{
		const type_info& Info = typeid(ResourceType);
		return std::dynamic_pointer_cast<ResourceType>(Find(Info.name(), _Name.data()));
	}

	static std::shared_ptr<UEngineResource> Find(std::string_view _ResourceName, std::string_view _Name);

	inline static bool IsExist(std::string_view _Name){return ResourceMap.contains(_Name.data());}
	inline static void Release(){ResourceMap.clear();}
	ENGINE_API static void LoadImages(std::vector<std::string> _Exts);

	template<typename ResType>
	ENGINE_API static void AddResource(std::shared_ptr<UEngineResource> _Resource, std::string_view _Name, std::string_view _Path)
	{
		const type_info& Info = typeid(ResType);
		AddResource(_Resource, Info.name(), _Name, _Path);
	}

	// 이 resources 관리 함수들은 전부다 core에서만 사용되게 하겠습니다.
	ENGINE_API static void AddResource(std::shared_ptr<UEngineResource> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path);

protected:

private:
	ENGINE_API static inline std::map<std::string, std::map<std::string, std::shared_ptr<UEngineResource>>> ResourceMap;

};

