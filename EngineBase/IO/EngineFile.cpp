#include "EnginePCH.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"

UEngineFile::UEngineFile()
{


}

UEngineFile::UEngineFile(std::string_view _Path)
	:UEnginePath(_Path)
{
}

UEngineFile::UEngineFile(std::filesystem::path _Path)
	:UEnginePath(_Path)
{
}

UEngineFile::~UEngineFile()
{
	Close();
}

void UEngineFile::Write(UEngineSerializer& _Ser)
{
	Write(_Ser.GetDataPtr(), _Ser.GetWriteOffset());
}

void UEngineFile::Read(UEngineSerializer& _Ser)
{
	// 파일 크기를 다 읽어서 

	int FileSize = GetFileSize();

	_Ser.DataResize(FileSize);

	Read(_Ser.GetDataPtr(), FileSize);
}

void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, this->ToString().c_str(), _Mode);

	// 파일을 열지 못한 경우
	if (nullptr == File)
	{
		MSGASSERT(this->ToString() + std::string("파일 오픈에 실패했습니다"));
	}
}


void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 쓸수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 사용하려고 했습니다.");
	}

	// w일 경우에 대한 예외처리
	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 읽을수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 읽으려고 했습니다.");
	}

	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

bool UEngineFile::IsExist()
{
	return std::filesystem::exists(Path);
}

int UEngineFile::GetFileSize()
{
	if (false == IsFile())
	{
		MSGASSERT(Path.string() + "는 파일이 아닙니다.");
		return -1;
	}

	return static_cast<int>(std::filesystem::file_size(Path));
}

BASE_API std::string UEngineFile::GetTextFromFile()
{
	UEngineSerializer Ser;
	Read(Ser);

	return reinterpret_cast<const char*>(Ser.GetDataPtr());
}

void UEngineFile::Close()
{
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

