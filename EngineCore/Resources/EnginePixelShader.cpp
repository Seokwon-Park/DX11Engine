#include "EnginePCH.h"
#include "EnginePixelShader.h"

UEnginePixelShader::UEnginePixelShader()
{
}

UEnginePixelShader::~UEnginePixelShader()
{
}

void UEnginePixelShader::CompilePath()
{
	UEngineShader::CompilePath();
	HRESULT HResult = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->
		CreatePixelShader(
			ShaderBlob->GetBufferPointer(),
			ShaderBlob->GetBufferSize(),
			nullptr,
			PixelShader.GetAddressOf());

	if (FAILED(HResult))
	{
		MSGASSERT("픽셀 셰이더 컴파일에 실패했습니다.");
	}
}

void UEnginePixelShader::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}
