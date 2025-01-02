#pragma once
#include <string>

class UEngineString
{
public:
	// constrcuter destructer
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	BASE_API static std::string ToUpper(std::string_view _String);

	BASE_API static std::wstring ToWString(std::string_view _String);

	BASE_API static int ExtractNumber(const std::string& _String, std::string_view _Pattern);

private:
	UEngineString();
	
};

