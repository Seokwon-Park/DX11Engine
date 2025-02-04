#include "EnginePCH.h"
#include "EngineString.h"
#include <EngineBase/EngineDebug.h>
#include <regex>

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}


std::string UEngineString::ToUpper(std::string_view _string)
{
	std::string Result = _string.data();
	Result.resize(_string.size());

	for (size_t i = 0; i < _string.size(); i++)
	{
		Result[i] = std::toupper(_string[i]);
	}
	
	return Result;
}

std::wstring UEngineString::ToWideString(std::string_view _String)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), static_cast<int>(_String.size()), nullptr, 0);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar 문자열 변환에 실패했습니다" + std::string(_String));
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), static_cast<int>(_String.size()), &Result[0], Size);

	if (0 == Size)
	{
		MSGASSERT("MultiByteToWideChar 문자열 변환에 실패했습니다" + std::string(_String));
		return L"";
	}

	return Result;
}



