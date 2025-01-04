#include "EnginePCH.h"
#include "EngineShader.h"
#include <EngineBase/EngineString.h>


UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
}

void UEngineShader::Compile()
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	UEngineFile File = std::string_view(Path.ToString());
	UINT CompilerFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	std::wstring FilePath = UEngineString::ToWString(File.ToString());

	std::string EntryPoint;
	std::string Target;
	switch (ShaderType)
	{
	case EShaderType::VS:
		EntryPoint = "vs_main";
		Target = "vs_5_0";
		break;
	case EShaderType::HS:
		EntryPoint = "hs_main";
		Target = "hs_5_0";
		break;
	case EShaderType::DS:
		break;
	case EShaderType::GS:
		break;
	case EShaderType::PS:
		EntryPoint = "ps_main";
		Target = "ps_5_0";
		break;
	case EShaderType::CS:
		break;
	default:
		break;
	}

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


//std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _FilePath)
//{
//	switch (UEngineCore::GetRendererAPI())
//	{
//	case ERendererAPI::DirectX11:
//		return std::make_shared<DX11Shader>(_FilePath);
//	case ERendererAPI::None:
//		return nullptr;
//	default:
//		return nullptr;
//	}
//}
//
//std::shared_ptr<UEngineShader> UEngineShader::Create(const std::string& _Name, const std::string& vertexSrc, const std::string& fragmentSrc)
//{
//	return std::shared_ptr<UEngineShader>();
//}

