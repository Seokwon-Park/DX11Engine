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

FSpriteData UEngineSprite::GetSpriteByIndex(size_t _Index)
{
	if (_Index >= SpriteData.size() || _Index < 0)
	{
		MSGASSERT("유효하지 않은 범위입니다.");
	}
	return SpriteData[_Index];
}


std::shared_ptr<UEngineSprite> UEngineSprite::CreateSprite(std::shared_ptr<UEngineTexture2D> _Texture)
{
	std::shared_ptr<UEngineSprite> NewSprite = std::make_shared<UEngineSprite>();
	UResourceManager::AddResource<UEngineSprite>(NewSprite, _Texture->GetName(), "");
	FSpriteData SpriteData;
	SpriteData.Texture = _Texture;
	SpriteData.Rect.CuttingPos = FVector2(0.0f, 0.0f);
	SpriteData.Rect.CuttingSize = FVector2(1.0f, 1.0f);
	SpriteData.Rect.Pivot = FVector2(0.5f, 0.5f);
	NewSprite->SpriteData.push_back(SpriteData);
	return NewSprite;
}

std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteFromFolder(std::string_view _Path)
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
		MSGASSERT("폴더에 이미지 파일이 없습니다.");
	}

	std::shared_ptr<UEngineSprite> NewSprite = std::make_shared<UEngineSprite>();
	UResourceManager::AddResource<UEngineSprite>(NewSprite, _Name, "");

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(Files[i].GetFileNameWithoutExtension());

		std::shared_ptr<UEngineTexture2D> Texture = UResourceManager::Find<UEngineTexture2D>(UpperName);

		if (nullptr == Texture)
		{
			MSGASSERT("텍스처를 먼저 로드하고 폴더 스프라이트를 만들어 주세요." + UpperName);
			return nullptr;
		}

		//NewSprite->Texture.push_back(Texture.get());

		FSpriteData SpriteData;
		SpriteData.Texture = Texture;
		SpriteData.Rect.CuttingPos = FVector2(0.0f, 0.0f);
		SpriteData.Rect.CuttingSize = FVector2(1.0f, 1.0f);
		SpriteData.Rect.Pivot = FVector2(0.5f, 0.5f);
		NewSprite->SpriteData.push_back(SpriteData);
	}

	return NewSprite;
}

std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteFromFolderSorted(std::string_view _Path, std::regex _Pattern)
{
	UEngineDirectory Dir = _Path;

	std::vector<UEngineFile> Files = Dir.GetAllFile(false, { ".png" });

	//_(숫자).PNG 형태의 꼴인 파일이 있다면 오름차순으로 정렬시킨다.
// 이거 왜필요함? _10.PNG다음에 _100과 _11이 있으면 _100이 먼저 저장되는 문제가 생긴다.
	std::sort(Files.begin(), Files.end(), [=](UEngineFile _FileA, UEngineFile _FileB)
		{
			std::smatch matchA, matchB;

			const std::string A = _FileA.GetCurrentName();
			const std::string B = _FileB.GetCurrentName();

			// 정규표현식 매칭
			bool isMatchA = std::regex_match(A, matchA, _Pattern);
			bool isMatchB = std::regex_match(B, matchB, _Pattern);

			if (isMatchA && isMatchB)
			{
				int suffixA = matchA[2].str().empty() ? 0 : std::stoi(matchA[2].str()); // "2" -> 2 (없으면 0)
				int suffixB = matchB[2].str().empty() ? 0 : std::stoi(matchB[2].str()); // "없음" -> 0
				int numberA = std::stoi(matchA[3].str()); // 66
				int numberB = std::stoi(matchB[3].str()); // 67

				// 1. baseA, baseB가 다르면 문자열 기준 정렬
				if (suffixA != suffixB) return suffixA < suffixB;
				// 3. _n_ 뒤 숫자 기준 정렬
				return numberA < numberB;
			}
			return A < B; // 정규식에 맞지 않는 경우 기본 사전순 정렬
		});
	std::shared_ptr<UEngineSprite> NewSprite = std::make_shared<UEngineSprite>();
	UResourceManager::AddResource<UEngineSprite>(NewSprite, Dir.GetCurrentName(), "");

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(Files[i].GetFileNameWithoutExtension());

		std::shared_ptr<UEngineTexture2D> Texture = UResourceManager::Find<UEngineTexture2D>(UpperName);

		if (nullptr == Texture)
		{
			MSGASSERT("텍스처를 먼저 로드하고 폴더 스프라이트를 만들어 주세요." + UpperName);
			return nullptr;
		}

		//NewSprite->Texture.push_back(Texture.get());

		FSpriteData SpriteData;
		SpriteData.Texture = Texture;
		SpriteData.Rect.CuttingPos = FVector2(0.0f, 0.0f);
		SpriteData.Rect.CuttingSize = FVector2(1.0f, 1.0f);
		SpriteData.Rect.Pivot = FVector2(0.5f, 0.5f);
		NewSprite->SpriteData.push_back(SpriteData);
	}

	return NewSprite;
}

void UEngineSprite::SetPivot(EPivotType _Pivot)
{
	FVector2 Pivot = FVector2(0.5f, 0.5f);
	switch (_Pivot)
	{
	case EPivotType::TopLeft:
		Pivot = FVector2(0.0f, 1.0f);
		break;
	case EPivotType::TopCenter:
		Pivot = FVector2(0.5f, 1.0f);
		break;
	case EPivotType::TopRight:
		Pivot = FVector2(1.0f, 1.0f);
		break;
	case EPivotType::LeftCenter:
		Pivot = FVector2(0.0f, 0.5f);
		break;
	case EPivotType::Center:
		Pivot = FVector2(0.5f, 0.5f);
		break;
	case EPivotType::RightCenter:
		Pivot = FVector2(1.0f, 0.5f);
		break;
	case EPivotType::BottomLeft:
		Pivot = FVector2(0.0f, 0.0f);
		break;
	case EPivotType::BottomCenter:
		Pivot = FVector2(0.5f, 0.0f);
		break;
	case EPivotType::BottomRight:
		Pivot = FVector2(1.0f, 0.0f);
		break;
	default:
		break;
	}
	SetPivot(Pivot);
}

void UEngineSprite::SetPivot(FVector2 _Pos)
{
	for (FSpriteData& Data : SpriteData)
	{
		Data.Rect.Pivot = _Pos;
	}
}

void UEngineSprite::SetPivot(FVector2 _Pos, Uint32 _Index)
{
	if (_Index >= SpriteData.size())
	{
		return;
	}
	SpriteData[_Index].Rect.Pivot = _Pos;
}

