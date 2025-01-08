#pragma once
#include <filesystem>

// 설명 :
class UEnginePath
{
public:
	// constrcuter destructer
	BASE_API UEnginePath();
	BASE_API UEnginePath(std::string_view _Path);
	BASE_API UEnginePath(std::filesystem::path _Path);
	BASE_API virtual ~UEnginePath();

	// delete Function
	BASE_API UEnginePath(const UEnginePath& _Other);
	BASE_API UEnginePath(UEnginePath&& _Other) noexcept;
	BASE_API UEnginePath& operator=(const UEnginePath& _Other);
	BASE_API UEnginePath& operator=(UEnginePath&& _Other) noexcept;

	inline std::filesystem::path GetPath() const { return Path; };
	BASE_API std::string ToString();
	BASE_API std::string GetCurrentName();
	BASE_API std::string GetFileExtension();
	BASE_API std::string GetFileNameWithoutExtension();
	BASE_API bool IsFile();
	BASE_API bool IsExists();
	BASE_API bool IsDirectory();
	BASE_API bool Move(std::string_view _Path);
	BASE_API void MoveParent();
	BASE_API void AppendDirectory(std::string_view _AppendName);

	//특정 디렉토리가 나올때까지 상위폴더로 이동
	BASE_API bool MoveParentToDirectory(std::string_view _Path);
protected:
	std::filesystem::path Path;

private:

};

