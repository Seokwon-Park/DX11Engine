#include "EnginePCH.h"
#include "EnginePath.h"

UEnginePath::UEnginePath() 
	:Path(std::filesystem::current_path())
{

}

UEnginePath::UEnginePath(std::string_view _Path)
	:Path(_Path)
{

}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	:Path(_Path)
{

}

UEnginePath::~UEnginePath()
{
}

UEnginePath::UEnginePath(const UEnginePath& _Other)
{
	Path = _Other.Path;
}

std::string UEnginePath::ToString()
{
	return Path.string();
}

std::string UEnginePath::GetPathName()
{
	return Path.filename().string();
}

std::string UEnginePath::GetFileExtension()
{
	return Path.extension().string();
}

bool UEnginePath::IsFile()
{
	return false == IsDirectory();
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

bool UEnginePath::Move(std::string_view _Path)
{
	AppendDirectory(_Path);

	if (false == IsExists())
	{
		MSGASSERT("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�.");
		return false;
	}

	return true;
}


bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("������ ��ΰ� ���� ��ΰ� �ƴմϴ�.");
		return false;
	}

	bool Result = false;
	std::filesystem::path CurPath;
	do
	{
		CurPath = DummyPath.Path;
		CurPath.append(_Path);
		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		DummyPath.MoveParent();
	} while (DummyPath.Path != DummyPath.Path.root_path());

	return Result;
}

void UEnginePath::AppendDirectory(std::string_view _AppendName)
{
	Path.append(_AppendName);
}
