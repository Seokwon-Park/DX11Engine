#pragma once

// 클래스 설명 :
class UEngineMaterial 
{
public:
	// Constrcuter Destructer
	UEngineMaterial();
	~UEngineMaterial();

	// Delete Function
	UEngineMaterial(const UEngineMaterial& _Other) = delete;
	UEngineMaterial(UEngineMaterial&& _Other) noexcept = delete;
	UEngineMaterial& operator=(const UEngineMaterial& _Other) = delete;
	UEngineMaterial& operator=(UEngineMaterial&& _Other) noexcept = delete;

	void SetVS(std::string_view _VSName);
	void SetVS(std::shared_ptr<class UEngineVertexShader> _VS);
	void SetPS(std::string_view _PSName);
	void SetPS(std::shared_ptr<class UEnginePixelShader> _PS);
	void Bind() const;

	ENGINE_API static std::shared_ptr<UEngineMaterial> Create(std::string_view _Name);
protected:

private:
	std::shared_ptr<class UEngineVertexShader> VertexShader;
	std::shared_ptr<class UEnginePixelShader> PixelShader;
	//std::shared_ptr<class UEngineRasterizerState> RasterizerState;
	//std::shared_ptr<class UEngineBlend> Blend;

	//D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	// UEngineCore::GetDevice().GetContext()->IASetPrimitiveTopology(Topology);
};
