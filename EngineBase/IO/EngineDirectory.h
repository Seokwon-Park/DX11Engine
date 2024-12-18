#pragma once
#include "EnginePath.h"

// Ό³Έν :
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	BASE_API UEngineDirectory();
	BASE_API UEngineDirectory(std::string_view _Path);
	BASE_API ~UEngineDirectory() override;

	// delete Function
	UEngineDirectory(const UEngineDirectory& _Other) = delete;
	UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	BASE_API std::vector<class UEngineFile> GetAllFile(bool _IsRecur = true);
	BASE_API UEngineFile GetFile(std::string_view _FileName);
protected:

private:
	void GetAllFileRecur(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result);

};

