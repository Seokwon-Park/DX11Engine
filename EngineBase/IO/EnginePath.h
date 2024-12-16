#pragma once
#include <filesystem>

// ���� :
class UEnginePath
{
public:
	// constrcuter destructer
	ENGINE_API UEnginePath();
	ENGINE_API UEnginePath(std::string_view _Path);
	ENGINE_API UEnginePath(std::filesystem::path _Path);
	ENGINE_API virtual ~UEnginePath();

	// delete Function
	UEnginePath(const UEnginePath& _Other);
	UEnginePath(UEnginePath&& _Other) noexcept = delete;
	UEnginePath& operator=(const UEnginePath& _Other) = delete;
	UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	inline std::filesystem::path GetPath() const { return Path; };
	ENGINE_API std::string ToString();
	std::string GetPathName();
	std::string GetFileExtension();
	bool IsFile();
	bool IsExists();
	bool IsDirectory();
	ENGINE_API bool Move(std::string_view _Path);
	void MoveParent();
	void AppendDirectory(std::string_view _AppendName);

	//Ư�� ���丮�� ���ö����� ���������� �̵�
	ENGINE_API bool MoveParentToDirectory(std::string_view _Path);
protected:
	std::filesystem::path Path;

private:

};

