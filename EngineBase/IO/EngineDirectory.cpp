#include "EnginePCH.h"
#include "EngineDirectory.h"
#include "EngineFile.h"


UEngineDirectory::UEngineDirectory()
	:UEnginePath()
{

}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	:UEnginePath(_Path)
{
}

UEngineDirectory::~UEngineDirectory()
{
}

void UEngineDirectory::GetAllFileRecur(std::filesystem::path _Path, std::vector<UEngineFile>& _Result)
{
	std::filesystem::directory_iterator DirItr = std::filesystem::directory_iterator(_Path);

	while (false == DirItr._At_end())
	{
		std::filesystem::path FilePath = *DirItr;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecur(FilePath, _Result);
			++DirItr;
			continue;
		}
		_Result.push_back(UEngineFile(FilePath));
		++DirItr;
	}
}

std::vector<UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecur)
{
	std::vector<UEngineFile> Result;

	// ����� ù��° ������ ����Ű�� ������
	std::filesystem::directory_iterator DirItr = std::filesystem::directory_iterator(Path);

	while (false == DirItr._At_end())
	{
		std::filesystem::path FilePath = *DirItr;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecur)
			{
				GetAllFileRecur(FilePath, Result);
			}
			++DirItr;
			continue;
		}
		Result.push_back(UEngineFile(FilePath));
		++DirItr;
	}

	return Result;
}

UEngineFile UEngineDirectory::GetFile(std::string_view _FileName)
{
	UEnginePath FilePath = Path;
	FilePath.AppendDirectory(_FileName);

	if (false == FilePath.IsExists())
	{
		MSGASSERT("�������� �ʴ� ������ ��üȭ�Ϸ��� �߽��ϴ�.");
	}

	return UEngineFile(FilePath.GetPath());
}