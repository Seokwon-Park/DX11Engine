#pragma once
#include <io.h>
#include "EnginePath.h"

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	BASE_API UEngineFile();
	BASE_API UEngineFile(std::string_view _Path);
	BASE_API UEngineFile(std::filesystem::path _Path);
	BASE_API ~UEngineFile() override;

	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	void Close();

	bool IsExist();

private:
	FILE* File = nullptr;
};

