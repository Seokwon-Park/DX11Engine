#include "EnginePCH.h"
#include "EngineShader.h"
#include "EngineBuffer.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineShaderResources.h>


UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
}

void UEngineShader::CompilePath()
{
	auto DeviceContext = UEngineCore::GetGraphicsDeviceContext();

	UEngineFile File = std::string_view(Path.ToString());
	UINT CompilerFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	std::wstring FilePath = UEngineString::ToWString(File.ToString());

	std::string Prefix = "";
	switch (ShaderType)
	{
	case EShaderType::VS:
		Prefix = "vs";
		break;
	case EShaderType::HS:
		Prefix = "hs";
		break;
	case EShaderType::DS:
		Prefix = "ds";
		break;
	case EShaderType::GS:
		Prefix = "gs";
		break;
	case EShaderType::PS:
		Prefix = "ps";
		break;
	case EShaderType::CS:
		Prefix = "cs";
		break;
	default:
		break;
	}
	std::string EntryPoint = Prefix + "_main";
	std::string Target = Prefix + "_5_0";

	HRESULT HResult = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, EntryPoint.c_str(), Target.c_str(), CompilerFlags, 0, ShaderBlob.GetAddressOf(), ShaderCompileErrorBlob.GetAddressOf());
	if (FAILED(HResult))
	{
		const char* ErrorString = NULL;
		if (HResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			ErrorString = "Could not compile shader; File not found";
		else if (ShaderCompileErrorBlob) {
			ErrorString = (const char*)ShaderCompileErrorBlob->GetBufferPointer();
		}
		MessageBoxA(0, ErrorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return;
	}

	HResult = D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_PPV_ARGS(&ShaderReflection));

	if (FAILED(HResult))
	{
		MSGASSERT("쉐이더 정보를 가져오는데 실패했습니다.");
		return;
	}

	ShaderResources = UEngineShaderResources::Create(GetThis<UEngineShader>());
}



//ENGINE_API std::vector<std::shared_ptr<UEngineShader>> UEngineShader::CreateShaders(std::string_view _FilePath, std::vector<EShaderType> _ShaderTypes)
//{
//	std::vector<std::shared_ptr<UEngineShader>> Result;
//	for (EShaderType ShaderType : _ShaderTypes)
//	{
//		Result.push_back(Create(_FilePath, ShaderType));
//	}
//	return Result;
//}

//std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _Name, const std::string& vertexSrc, const std::string& fragmentSrc)
//{
//	return std::shared_ptr<UEngineShader>();
//}

