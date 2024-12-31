#include "EnginePCH.h"
#include "EngineSprite.h"
#include "ResourceManager.h"
#include <EngineBase/EngineString.h>

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

ENGINE_API std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteFromFolder(std::string_view _Path)
{
	UEngineDirectory Dir = _Path;

	return CreateSpriteFromFolder(Dir.GetCurrentName(), _Path);
}

ENGINE_API std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteFromFolder(std::string_view _Name, std::string_view _Path)
{
	UEngineDirectory Dir = _Path;

	std::vector<UEngineFile> Files = Dir.GetAllFile(false, { ".png" });

	if (0 == Files.size())
	{
		MSGASSERT("������ �̹��� ������ �����ϴ�.");
	}

	std::shared_ptr<UEngineSprite> NewSprite = std::make_shared<UEngineSprite>();
	UResourceManager::AddResource<UEngineSprite>(NewSprite, _Name, "");

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(Files[i].GetCurrentName());

		std::shared_ptr<UEngineTexture> Texture = UResourceManager::Find<UEngineTexture>(UpperName);

		if (nullptr == Texture)
		{
			MSGASSERT("�ؽ�ó�� ���� �ε��ϰ� ���� ��������Ʈ�� ����� �ּ���." + UpperName);
			return nullptr;
		}

		//NewSprite->Texture.push_back(Texture.get());

		FSpriteData SpriteData;
		SpriteData.Texture = Texture.get();
		SpriteData.Rect.CuttingPos = { 0.0f, 0.0f };
		SpriteData.Rect.CuttingSize = { 1.0f, 1.0f };
		//SpriteData.Pivot = { 0.5f, 0.0f };
		NewSprite->SpriteDatas.push_back(SpriteData);
	}

	return NewSprite;
}

