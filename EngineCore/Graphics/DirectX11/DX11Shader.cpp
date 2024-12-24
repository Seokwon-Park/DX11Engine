#include "EnginePCH.h"
#include "EngineCore.h"
#include "DX11Shader.h"
#include "DX11DeviceContext.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>

DX11Shader::DX11Shader(const std::string& _FilePath)
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineCore");
	CurDir.Move("Graphics");
	CurDir.Move("Shaders");
	UEngineFile File = CurDir.GetFile("SpriteShader.hlsl");
	//CreateSamplerState();

	UINT CompilerFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	std::wstring FilePath = UEngineString::ToWString(File.ToString());
	ComPtr<ID3DBlob> VertexShaderBlob;
	ComPtr<ID3DBlob> ShaderCompileErrorsBlob;
	HRESULT HResult = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, "vs_main", "vs_5_0", CompilerFlags, 0, &VertexShaderBlob, &ShaderCompileErrorsBlob);
	if (FAILED(HResult))
	{
		const char* ErrorString = NULL;
		if (HResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			ErrorString = "Could not compile shader; file not found";
		else if (ShaderCompileErrorsBlob) {
			ErrorString = (const char*)ShaderCompileErrorsBlob->GetBufferPointer();
			//ShaderCompileErrorsBlob->Release();
		}
		MessageBoxA(0, ErrorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return;
	}
	HResult = DeviceContext->GetDevice()->
		CreateVertexShader(
			VertexShaderBlob->GetBufferPointer(),
			VertexShaderBlob->GetBufferSize(),
			nullptr,
			VertexShader.GetAddressOf());
	assert(SUCCEEDED(HResult));

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
		InputLayOutData.push_back(Desc);
	}


	// 쉐이더에서 어떤 인풋레이아웃을 사용하는지 알려줘.
	HRESULT Result = DeviceContext->GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		static_cast<unsigned int>(InputLayOutData.size()),
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		InputLayout.GetAddressOf());

	if (S_OK != Result)
	{
		std::cerr << "CreateInputLayout failed with HRESULT: " << std::hex << Result << std::endl;
		MSGASSERT("인풋 레이아웃 생성에 실패했습니다");
	}
	
	// Create Pixel Shader
	ComPtr<ID3DBlob> PixelShaderBlob;
	HResult = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, "ps_main", "ps_5_0", CompilerFlags, 0, &PixelShaderBlob, &ShaderCompileErrorsBlob);
	if (FAILED(HResult))
	{
		const char* ErrorString = NULL;
		if (HResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			ErrorString = "Could not compile shader; file not found";
		else if (ShaderCompileErrorsBlob) {
			ErrorString = (const char*)ShaderCompileErrorsBlob->GetBufferPointer();
			//ShaderCompileErrorsBlob->Release();
		}
		MessageBoxA(0, ErrorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return;
	}

	HResult = DeviceContext->GetDevice()->
		CreatePixelShader(
			PixelShaderBlob->GetBufferPointer(),
			PixelShaderBlob->GetBufferSize(),
			nullptr,
			&PixelShader);
	assert(SUCCEEDED(HResult));
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
