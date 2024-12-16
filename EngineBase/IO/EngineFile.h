#pragma once
#include <io.h>
#include "EnginePath.h"

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	ENGINE_API UEngineFile();
	ENGINE_API UEngineFile(std::string_view _Path);
	ENGINE_API UEngineFile(std::filesystem::path _Path);
	ENGINE_API ~UEngineFile();

	//���Ͽ� _Ptr ����
	void Write(const void* _Ptr, size_t _Size);
	//���� �б�
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExist();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

