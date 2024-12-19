#pragma once
#include <filesystem>

// ���� :
class UEnginePath
{
public:
	// constrcuter destructer
	BASE_API UEnginePath();
	BASE_API UEnginePath(std::string_view _Path);
	BASE_API UEnginePath(std::filesystem::path _Path);
	BASE_API virtual ~UEnginePath();

	// delete Function
	UEnginePath(const UEnginePath& _Other);
	UEnginePath(UEnginePath&& _Other) noexcept = delete;
	UEnginePath& operator=(const UEnginePath& _Other) = delete;
	UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	inline std::filesystem::path GetPath() const { return Path; };
	BASE_API std::string ToString();
	BASE_API std::string GetPathName();
	std::string GetFileExtension();
	bool IsFile();
	bool IsExists();
	bool IsDirectory();
	BASE_API bool Move(std::string_view _Path);
	void MoveParent();
	void AppendDirectory(std::string_view _AppendName);

	//Ư�� ���丮�� ���ö����� ���������� �̵�
	BASE_API bool MoveParentToDirectory(std::string_view _Path);
protected:
	std::filesystem::path Path;

private:

};

