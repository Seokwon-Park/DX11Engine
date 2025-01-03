#include "EnginePCH.h"
#include "EngineVertexShader.h"
#include "EngineDeviceContext.h"

UEngineVertexShader::UEngineVertexShader(std::string_view _FilePath, EShaderType _ShaderType)
{
	HRESULT HResult = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->
		CreateVertexShader(
			ShaderBlob->GetBufferPointer(),
			ShaderBlob->GetBufferSize(),
			nullptr,
			VertexShader.GetAddressOf());

	if (FAILED(HResult))
	{
		MSGASSERT("���ؽ� ���̴� �����Ͽ� �����߽��ϴ�.")
	}
}

UEngineVertexShader::~UEngineVertexShader()
{
}

void UEngineVertexShader::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);

}
