#pragma once
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineResource.h>
#include <EngineCore/Resources/EngineTexture.h>

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

	ENGINE_API static void InitResources();
	static void InitVertexBuffer();
	static void InitIndexBuffer();
	static void InitMesh();

	template<typename ResourceType>
	static std::shared_ptr<ResourceType> Find(std::string_view _Name)
	{
		const type_info& Info = typeid(ResourceType);
		return std::dynamic_pointer_cast<ResourceType>(Find(Info.name(), _Name.data()));
	}
	template<typename ResourceType>
	inline static void AddResource(std::shared_ptr<UEngineResource> _Resource, std::string_view _Name, std::string_view _Path)
	{
		const type_info& Info = typeid(ResourceType);
		AddResource(_Resource, Info.name(), _Name, _Path);
	}

	template<typename ResourceType>
	inline static void LoadResourcesFromDirectory(std::vector<std::string> _Exts, std::string_view _DirName)
	{
		const type_info& Info = typeid(ResourceType);
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		if (false == Dir.Move(_DirName))
		{
			MSGASSERT(std::string(_DirName) + " 폴더를 찾지 못했습니다.");
			return;
		}
		std::vector<UEngineFile> Files = Dir.GetAllFile(true, _Exts);
		for (size_t i = 0; i < Files.size(); i++)
		{
			std::string FilePath = Files[i].ToString();
			std::shared_ptr<ResourceType> Resource = ResourceType::Create(FilePath);
			AddResource(Resource, Info.name(), Files[i].GetCurrentName(), FilePath);
		}
	}

	template<typename ResourceType>
	ENGINE_API inline static std::vector<ResourceType> LoadAllResources()
	{
		const type_info& Info = typeid(ResourceType);
		std::vector<ResourceType> Result;
		auto Resources = ResourceMap[Info.name()];
		for (auto [Name, Resource] : Resources)
		{
			Result.push_back(Resources);
		}
		return Resources;
	}

	inline static bool IsExist(std::string_view _Name){return ResourceMap.contains(_Name.data());}
	inline static void Release(){ResourceMap.clear();}



	ENGINE_API static std::shared_ptr<UEngineResource> Find(std::string_view _ResourceName, std::string_view _Name);
	ENGINE_API static void AddResource(std::shared_ptr<UEngineResource> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path);

protected:

private:
	ENGINE_API static std::map<std::string, std::map<std::string, std::shared_ptr<UEngineResource>>> ResourceMap;

};

