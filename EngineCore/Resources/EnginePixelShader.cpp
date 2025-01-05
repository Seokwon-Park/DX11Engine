#include "EnginePCH.h"
#include "EnginePixelShader.h"

UEnginePixelShader::UEnginePixelShader()
{
}

UEnginePixelShader::~UEnginePixelShader()
{
}

void UEnginePixelShader::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}

void UEnginePixelShader::Compile()
{
	UEngineShader::Compile();
	HRESULT HResult = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->
		CreatePixelShader(
			ShaderBlob->GetBufferPointer(),
			ShaderBlob->GetBufferSize(),
			nullptr,
			PixelShader.GetAddressOf());

	if (FAILED(HResult))
	{
		MSGASSERT("�ȼ� ���̴� �����Ͽ� �����߽��ϴ�.");
	}
}
