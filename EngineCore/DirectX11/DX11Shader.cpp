#include "EnginePCH.h"
#include "DX11Shader.h"
#include "EngineCore.h"
#include "Components/CameraComponent.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineSprite.h>
#include "EngineDeviceContext.h"

DX11Shader::DX11Shader(std::string_view _FilePath, EShaderType _ShaderType)
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	UEngineFile File = _FilePath;
	UINT CompilerFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	std::wstring FilePath = UEngineString::ToWString(File.ToString());

	std::string EntryPoint;
	std::string Target;
	switch (_ShaderType)
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

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DeviceContext->GetDevice()->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
}

DX11Shader::~DX11Shader()
{
}

//VS
DX11VertexShader::DX11VertexShader(std::string_view _FilePath, EShaderType _ShaderType)
	:DX11Shader(_FilePath, _ShaderType)
{

}

DX11VertexShader::~DX11VertexShader()
{
}

void DX11VertexShader::Bind() const
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	DeviceContext->GetContext()->PSSetSamplers(0, 1, SamplerState.GetAddressOf());
}


//void DX11VertexShader::SetVertexConstants(VertexConstant _Data)
//{
//	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
//
//	VertexCBuffer.Reset();
//	D3D11_BUFFER_DESC BufferInfo = { 0 };
//	BufferInfo.ByteWidth = sizeof(VertexConstant);
//	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
//	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
//
//	if (S_OK != DeviceContext->GetDevice()->CreateBuffer(&BufferInfo, nullptr, VertexCBuffer.GetAddressOf()))
//	{
//		MSGASSERT("상수버퍼 생성에 실패했습니다..");
//		return;
//	}
//
//	D3D11_MAPPED_SUBRESOURCE Data = {};
//	DeviceContext->GetContext()->Map(VertexCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//	// Data.pData 그래픽카드와 연결된 주소값.
//	if (nullptr == Data.pData)
//	{
//		MSGASSERT("그래픽카드가 수정을 거부했습니다.");
//	}
//
//	memcpy_s(Data.pData, sizeof(VertexConstant), &_Data, sizeof(VertexConstant));
//	DeviceContext->GetContext()->Unmap(VertexCBuffer.Get(), 0);
//
//	// 같은 상수버퍼를 
//	ID3D11Buffer* ArrPtr[16] = { VertexCBuffer.Get() };
//	DeviceContext->GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
//}
//
//void DX11VertexShader::SetSpriteConstants(FSpriteRect _Data)
//{
//	UVBuffer.Reset();
//	D3D11_BUFFER_DESC BufferInfo = { 0 };
//	BufferInfo.ByteWidth = sizeof(FSpriteRect);
//	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
//	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
//
//	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
//
//	if (S_OK != DeviceContext->GetDevice()->CreateBuffer(&BufferInfo, nullptr, UVBuffer.GetAddressOf()))
//	{
//		MSGASSERT("상수버퍼 생성에 실패했습니다..");
//		return;
//	}
//
//	D3D11_MAPPED_SUBRESOURCE Data = {};
//	DeviceContext->GetContext()->Map(UVBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//	// Data.pData 그래픽카드와 연결된 주소값.
//	if (nullptr == Data.pData)
//	{
//		MSGASSERT("그래픽카드가 수정을 거부했습니다.");
//	}
//
//	memcpy_s(Data.pData, sizeof(FSpriteRect), &_Data, sizeof(FSpriteRect));
//	DeviceContext->GetContext()->Unmap(UVBuffer.Get(), 0);
//
//	// 같은 상수버퍼를 
//	ID3D11Buffer* ArrPtr[16] = { UVBuffer.Get() };
//	DeviceContext->GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
//}

DX11PixelShader::DX11PixelShader(std::string_view _FilePath, EShaderType _ShaderType)
	:DX11Shader(_FilePath, _ShaderType)
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	HRESULT HResult = DeviceContext->GetDevice()->
		CreatePixelShader(
			ShaderBlob->GetBufferPointer(),
			ShaderBlob->GetBufferSize(),
			nullptr,
			PixelShader.GetAddressOf());

	if (FAILED(HResult))
	{
		MSGASSERT("픽셀 셰이더 컴파일에 실패했습니다.")
	}
}

DX11PixelShader::~DX11PixelShader()
{
}

void DX11PixelShader::Bind() const
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	DeviceContext->GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}
