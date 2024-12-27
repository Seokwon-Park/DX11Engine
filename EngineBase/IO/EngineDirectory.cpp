#include "EnginePCH.h"
#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineString.h"


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


std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive, const std::vector<std::string>& _Exts)
{
	std::vector<std::string> UpperExts;
	for (size_t i = 0; i < _Exts.size(); i++)
	{
		UpperExts.push_back(UEngineString::ToUpper(_Exts[i]));
	}

	std::vector<class UEngineFile> Result;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(Path);

	while (false == DirIter._At_end())
	{
		std::filesystem::path FilePath = *DirIter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result, _Exts);
			}
		}
		else if (true == IsTargetExt(_Exts, Path))
		{
			Result.push_back(UEngineFile(FilePath));
		}
		++DirIter;
	}

	return Result;
}

void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path, std::vector<UEngineFile>& _Result, const std::vector<std::string>& _Exts)
{
	std::filesystem::directory_iterator DirItr = std::filesystem::directory_iterator(_Path);

	while (false == DirItr._At_end())
	{
		std::filesystem::path FilePath = *DirItr;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result, _Exts);
		}
		else if (true == IsTargetExt(_Exts, Path))
		{
			_Result.push_back(UEngineFile(FilePath));
		}
		++DirItr;
	}
}


bool UEngineDirectory::IsTargetExt(const std::vector<std::string>& _UpperExts, UEnginePath _Path)
{
	for (size_t i = 0; i < _UpperExts.size(); i++)
	{
		std::string CurUpperExt = UEngineString::ToUpper(_Path.GetFileExtension());

		if (CurUpperExt == _UpperExts[i])
		{
			return true;
		}
	}
	return false;
}

UEngineFile UEngineDirectory::GetFile(std::string_view _FileName)
{
	UEnginePath FilePath = Path;
	FilePath.AppendDirectory(_FileName);

	if (false == FilePath.IsExists())
	{
		MSGASSERT("존재하지 않는 파일을 객체화하려고 했습니다.");
	}

	return UEngineFile(FilePath.GetPath());
}