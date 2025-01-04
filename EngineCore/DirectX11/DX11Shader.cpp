#include "EnginePCH.h"
#include "DX11Shader.h"


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
//		MSGASSERT("������� ������ �����߽��ϴ�..");
//		return;
//	}
//
//	D3D11_MAPPED_SUBRESOURCE Data = {};
//	DeviceContext->GetContext()->Map(VertexCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//	// Data.pData �׷���ī��� ����� �ּҰ�.
//	if (nullptr == Data.pData)
//	{
//		MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
//	}
//
//	memcpy_s(Data.pData, sizeof(VertexConstant), &_Data, sizeof(VertexConstant));
//	DeviceContext->GetContext()->Unmap(VertexCBuffer.Get(), 0);
//
//	// ���� ������۸� 
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
//		MSGASSERT("������� ������ �����߽��ϴ�..");
//		return;
//	}
//
//	D3D11_MAPPED_SUBRESOURCE Data = {};
//	DeviceContext->GetContext()->Map(UVBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//	// Data.pData �׷���ī��� ����� �ּҰ�.
//	if (nullptr == Data.pData)
//	{
//		MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
//	}
//
//	memcpy_s(Data.pData, sizeof(FSpriteRect), &_Data, sizeof(FSpriteRect));
//	DeviceContext->GetContext()->Unmap(UVBuffer.Get(), 0);
//
//	// ���� ������۸� 
//	ID3D11Buffer* ArrPtr[16] = { UVBuffer.Get() };
//	DeviceContext->GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
//}


