#pragma once
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineResource.h>
#include <EngineCore/Resources/EngineTexture.h>

// 설명 :
class UResourceManager
{
public:
	// constrcuter destructer
	~UResourceManager();

	// delete Function
	UResourceManager(const UResourceManager& _Other) = delete;
	UResourceManager(UResourceManager&& _Other) noexcept = delete;
	UResourceManager& operator=(const UResourceManager& _Other) = delete;
	UResourceManager& operator=(UResourceManager&& _Other) noexcept = delete;

	ENGINE_API static void CreateDefaultResources();
	static void CreateDefaultShader();
	static void CreateDefaultVertexBuffer();
	static void CreateDefaultInputLayout();
	static void CreateDefaultIndexBuffer();
	static void CreateDefaultSamplerState();
	static void CreateDefaultMesh();
	static void CreateDefaultMaterial();

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
			std::shared_ptr<ResourceType> Resource = ResourceType::Create(Files[i].GetCurrentName(), FilePath);
		}
	}

	template<typename ResourceType>
	inline static std::vector<std::shared_ptr<ResourceType>> GetAllResources()
	{
		//if (std::is_base_of_v(ResourceType, UEngineTexture2D))
		//	return;
		const type_info& Info = typeid(ResourceType);
		auto Resources = ResourceMap[Info.name()];
		std::vector<std::shared_ptr<ResourceType>> Result;
		for (auto [Name, Resource] : Resources)
		{
			std::shared_ptr<ResourceType> Res = std::static_pointer_cast<ResourceType>(Resource);
			Result.push_back(Res);
		}
		return Result;
	}

	template <typename ResourceType>
	inline static bool IsExist(std::string_view _Name) {
		const type_info& Info = typeid(ResourceType);
		return ResourceMap[Info.name()].contains(_Name.data());
	}
	inline static void Release() { ResourceMap.clear(); }

	ENGINE_API static std::shared_ptr<UEngineResource> Find(std::string_view _ResourceType, std::string_view _ResourceName);
	ENGINE_API static void AddResource(std::shared_ptr<UEngineResource> _Resource, const std::string_view _Info, std::string_view _Name, std::string_view _Path);

protected:

private:
	UResourceManager();

	ENGINE_API static std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<UEngineResource>>> ResourceMap;

};

