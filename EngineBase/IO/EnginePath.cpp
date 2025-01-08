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

UEnginePath::UEnginePath(UEnginePath&& _Other) noexcept
{
	Path = _Other.Path;
}

UEnginePath& UEnginePath::operator=(const UEnginePath& _Other)
{
	if (this != &_Other)
	{
		Path = _Other.Path;
	}

	return *this;
}

BASE_API UEnginePath& UEnginePath::operator=(UEnginePath&& _Other) noexcept
{
	Path = _Other.Path;

	return *this;
}

std::string UEnginePath::ToString()
{
	return Path.string();
}

std::string UEnginePath::GetCurrentName()
{
	return Path.filename().string();
}

std::string UEnginePath::GetFileExtension()
{
	return Path.extension().string();
}

BASE_API std::string UEnginePath::GetFileNameWithoutExtension()
{
	return Path.stem().string();
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
		MSGASSERT("존재하지 않는 경로로 이동하려고 했습니다.");
		return false;
	}

	return true;
}


bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("설정된 경로가 폴더 경로가 아닙니다.");
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

