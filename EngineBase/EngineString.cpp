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

int UEngineString::ExtractNumber(const std::string& _String, std::string_view _Pattern)
{
	std::regex RegexPattern(_Pattern.data());
	std::smatch Match;
	if (std::regex_search(_String, Match, RegexPattern)) {
		return std::stoi(Match[1]); // 첫 번째 캡처 그룹에서 숫자를 추출
	}
	return -1; // 유효하지 않은 파일일 경우 -1 반환
}


