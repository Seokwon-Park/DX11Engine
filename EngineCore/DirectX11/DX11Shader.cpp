#include "EnginePCH.h"
#include "DX11Shader.h"
#include "EngineCore.h"
#include "DX11DeviceContext.h"
#include "Components/CameraComponent.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineSprite.h>

DX11Shader::DX11Shader(const std::string& _FilePath)
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineCore");
	CurDir.Move("Shaders");
	UEngineFile File = CurDir.GetFile("SpriteShader.hlsl");

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

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "TEXCOORD";
		Desc.SemanticIndex = 0;
		Desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		Desc.InputSlot = 0;
		Desc.AlignedByteOffset = 32;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}


	// ���̴����� � ��ǲ���̾ƿ��� ����ϴ��� �˷���.
	HRESULT Result = DeviceContext->GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		static_cast<unsigned int>(InputLayOutData.size()),
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		InputLayout.GetAddressOf());

	if (S_OK != Result)
	{
		std::cerr << "CreateInputLayout failed with HRESULT: " << std::hex << Result << std::endl;
		MSGASSERT("��ǲ ���̾ƿ� ������ �����߽��ϴ�");
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

void DX11Shader::SetVertexConstants(VertexConstant _Data)
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	VertexCBuffer.Reset();
	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(VertexConstant);
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != DeviceContext->GetDevice()->CreateBuffer(&BufferInfo, nullptr, VertexCBuffer.GetAddressOf()))
	{
		MSGASSERT("������� ������ �����߽��ϴ�..");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};
	DeviceContext->GetContext()->Map(VertexCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Data.pData �׷���ī��� ����� �ּҰ�.
	if (nullptr == Data.pData)
	{
		MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
	}

	memcpy_s(Data.pData, sizeof(VertexConstant), &_Data, sizeof(VertexConstant));
	DeviceContext->GetContext()->Unmap(VertexCBuffer.Get(), 0);

	// ���� ������۸� 
	ID3D11Buffer* ArrPtr[16] = { VertexCBuffer.Get() };
	DeviceContext->GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
}

void DX11Shader::SetSpriteConstants(FSpriteRect _Data)
{
	UVBuffer.Reset();
	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(FSpriteRect);
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	if (S_OK != DeviceContext->GetDevice()->CreateBuffer(&BufferInfo, nullptr, UVBuffer.GetAddressOf()))
	{
		MSGASSERT("������� ������ �����߽��ϴ�..");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};
	DeviceContext->GetContext()->Map(UVBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Data.pData �׷���ī��� ����� �ּҰ�.
	if (nullptr == Data.pData)
	{
		MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
	}

	memcpy_s(Data.pData, sizeof(FSpriteRect), &_Data, sizeof(FSpriteRect));
	DeviceContext->GetContext()->Unmap(UVBuffer.Get(), 0);

	// ���� ������۸� 
	ID3D11Buffer* ArrPtr[16] = { UVBuffer.Get() };
	DeviceContext->GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
}

void DX11Shader::Bind() const
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	DeviceContext->GetContext()->PSSetSamplers(0, 1, SamplerState.GetAddressOf());
	DeviceContext->GetContext()->IASetInputLayout(InputLayout.Get());
	DeviceContext->GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}
