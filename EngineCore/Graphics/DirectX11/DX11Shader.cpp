#include "EnginePCH.h"
#include "EngineCore.h"
#include "DX11Shader.h"
#include "DX11DeviceContext.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>

DX11Shader::DX11Shader(const std::string& filepath)
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineCore");
	CurDir.Move("Graphics");
	CurDir.Move("Shaders");
	UEngineFile File = CurDir.GetFile("SpriteShader.hlsl");
	//CreateSamplerState();

	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	std::wstring FilePath = UEngineString::ToWString(File.ToString());
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> shaderCompileErrorsBlob;
	HRESULT hResult = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, "vs_main", "vs_5_0", compileFlags, 0, &vsBlob, &shaderCompileErrorsBlob);
	if (FAILED(hResult))
	{
		const char* errorString = NULL;
		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			errorString = "Could not compile shader; file not found";
		else if (shaderCompileErrorsBlob) {
			errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
			shaderCompileErrorsBlob->Release();
		}
		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return;
	}
	hResult = DeviceContext->GetDevice()->
		CreateVertexShader(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			VertexShader.GetAddressOf());
	assert(SUCCEEDED(hResult));

	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.SemanticIndex = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.InputSlot = 0;
		Desc.AlignedByteOffset = 0;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.SemanticIndex = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.InputSlot = 0;
		Desc.AlignedByteOffset = 16;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.InstanceDataStepRate = 0;

		// �ν��Ͻ��� �����Ҷ� �̾߱� �ϰڽ��ϴ�.
		InputLayOutData.push_back(Desc);
	}

	// ���̴����� � ��ǲ���̾ƿ��� ����ϴ��� �˷���.
	HRESULT Result = DeviceContext->GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		InputLayOutData.size(),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&InputLayout);

	if (S_OK != Result)
	{
		std::cerr << "CreateInputLayout failed with HRESULT: " << std::hex << Result << std::endl;
		MSGASSERT("��ǲ ���̾ƿ� ������ �����߽��ϴ�");
	}
	//DeviceContext->GetDevice()->CreateInputLayout(DeviceContext->GetInputElements().data(), UINT(DeviceContext->GetInputElements().size()),
	//	vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
	//	&InputLayout);

	// Create Pixel Shader
	ID3DBlob* psBlob;
	hResult = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, "ps_main", "ps_5_0", compileFlags, 0, &psBlob, &shaderCompileErrorsBlob);
	if (FAILED(hResult))
	{
		const char* errorString = NULL;
		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			errorString = "Could not compile shader; file not found";
		else if (shaderCompileErrorsBlob) {
			errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
			shaderCompileErrorsBlob->Release();
		}
		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return;
	}

	hResult = DeviceContext->GetDevice()->
		CreatePixelShader(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&PixelShader);
	assert(SUCCEEDED(hResult));
	vsBlob->Release();
	psBlob->Release();
}

DX11Shader::~DX11Shader()
{
}

void DX11Shader::Bind() const
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	//DeviceContext->GetContext()->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
	DeviceContext->GetContext()->IASetInputLayout(InputLayout.Get());
	DeviceContext->GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}
