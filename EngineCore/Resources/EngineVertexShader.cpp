#include "EnginePCH.h"
#include "EngineVertexShader.h"
#include "EngineDeviceContext.h"

UEngineVertexShader::UEngineVertexShader()
{
}

UEngineVertexShader::~UEngineVertexShader()
{
}

void UEngineVertexShader::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);

}

void UEngineVertexShader::Compile()
{
	UEngineShader::Compile();
	HRESULT HResult = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->
		CreateVertexShader(
			ShaderBlob->GetBufferPointer(),
			ShaderBlob->GetBufferSize(),
			nullptr,
			VertexShader.GetAddressOf());

	if (FAILED(HResult))
	{
		MSGASSERT("���ؽ� ���̴� �����Ͽ� �����߽��ϴ�.");
	}
}
